#include "base/logging.h"
#include "base/run_loop.h"
#include "base/task/single_thread_task_executor.h"
#include "base/threading/thread.h"
#include "mojo/core/embedder/embedder.h"
#include "mojo/core/embedder/scoped_ipc_support.h"
#include "mojo/public/c/system/data_pipe.h"
#include "mojo/public/c/system/message_pipe.h"
#include "mojo/public/cpp/system/buffer.h"
#include "mojo/public/cpp/system/data_pipe.h"
#include "mojo/public/cpp/system/message_pipe.h"

#include "../cc_chromium_test.h"

TEST(CCChromiumTest, TestMojoSingleProcess) {
    
    mojo::core::Init();
    base::Thread ipc_thread("ipc!");
    ipc_thread.StartWithOptions(
        base::Thread::Options(base::MessagePumpType::IO, 0));
 
#if defined(OS_WIN)
    logging::LoggingSettings logging_setting;
    logging_setting.logging_dest = logging::LOG_TO_STDERR;
    logging::SetLogItems(true, true, false, false);
    logging::InitLogging(logging_setting);
#endif

    // As long as this object is alive, all Mojo API surface relevant to IPC
    // connections is usable, and message pipes which span a process boundary will
    // continue to function.
    mojo::core::ScopedIPCSupport ipc_support(
        ipc_thread.task_runner(),
        mojo::core::ScopedIPCSupport::ShutdownPolicy::CLEAN);

    MojoResult result = MOJO_RESULT_OK;

    // 使用C++接口创建一条 MessagePipe
    mojo::MessagePipe pipe;
    // 使用 C++ 接口发送一条消息
    {
        const char kMessage[] = "HELLO";
        result =
            mojo::WriteMessageRaw(pipe.handle0.get(), kMessage, sizeof(kMessage),
                                  nullptr, 0, MOJO_WRITE_MESSAGE_FLAG_NONE);
        DCHECK_EQ(result, MOJO_RESULT_OK);
        LOG(INFO) << "send: " << kMessage;
    }
    // 使用 C++ 接口接收一条消息
    {
        std::vector<uint8_t> data;
        result = mojo::ReadMessageRaw(pipe.handle1.get(), &data, nullptr,
                                      MOJO_READ_MESSAGE_FLAG_NONE);
        DCHECK_EQ(result, MOJO_RESULT_OK);
        LOG(INFO) << "receive msg: " << (char *)&data[0];
    }

    // 使用 C++ 接口创建一条 DataPipe，DataPipe 是单向的
    mojo::ScopedDataPipeProducerHandle producer;
    mojo::ScopedDataPipeConsumerHandle consumer;
    // 内部涉及系统资源的分配，可能会失败，因此不建议使用 mojo::DataPipe
    // 来创建，会导致崩溃
    result = mojo::CreateDataPipe(nullptr, producer, consumer);
    // 使用 DataPipe 写数据
    {
        const char kMessage[] = "DataPipe";
        uint32_t length = sizeof(kMessage);
        result = producer->WriteData(kMessage, &length, MOJO_WRITE_DATA_FLAG_NONE);
        DCHECK_EQ(result, MOJO_RESULT_OK);
        LOG(INFO) << "send data: " << kMessage;
    }
    // 使用 DataPipe 读数据
    {
        char buffer[100];
        uint32_t num_bytes = 100;
        result = consumer->ReadData(buffer, &num_bytes, MOJO_READ_DATA_FLAG_NONE);
        DCHECK_EQ(result, MOJO_RESULT_OK);
        LOG(INFO) << "receive data: " << buffer;
    }

    // 使用 C++ 接口创建一个 SharedBuffer
    // Shared Buffer 内部也使用 Shared Memory 实现
    mojo::ScopedSharedBufferHandle buffer =
        mojo::SharedBufferHandle::Create(4096);
    // clone一个buffer的句柄，该句柄和buffer指向相同的内存，内部有引用计数
    // 当计数为0的时候，句柄指向的内存会被销毁
    // 这里只是为了演示Clone，并不是必须的
    mojo::ScopedSharedBufferHandle buffer_clone =
        buffer->Clone(mojo::SharedBufferHandle::AccessMode::READ_WRITE);
    // 向 SharedBuffer 写数据
    {
        const std::string kMessage("SharedBuffer\0", 13);
        mojo::ScopedSharedBufferMapping mapping = buffer->Map(kMessage.length());
        DCHECK(mapping);
        std::copy(kMessage.begin(), kMessage.end(),
                  static_cast<char *>(mapping.get()));
        LOG(INFO) << "write buffer: " << kMessage;
    }
    // 从 SharedBuffer 读数据
    {
        mojo::ScopedSharedBufferMapping mapping = buffer_clone->Map(64);
        LOG(INFO) << "read buffer: " << static_cast<char *>(mapping.get());
    }

    // 创建消息循环
    base::SingleThreadTaskExecutor main_thread_task_executor;
    base::RunLoop run_loop;
    run_loop.RunUntilIdle();
}