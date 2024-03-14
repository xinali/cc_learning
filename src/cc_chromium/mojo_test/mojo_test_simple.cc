#include "base/at_exit.h"
#include "base/run_loop.h"
#include "base/task/thread_pool/thread_pool_instance.h"
#include "base/threading/thread.h"

#include "mojo/core/embedder/embedder.h"
#include "mojo/core/embedder/scoped_ipc_support.h"
#include "mojo/public/cpp/platform/platform_channel.h"
#include "mojo/public/cpp/system/invitation.h"
#include "mojo/public/cpp/system/message_pipe.h"

// For bindings API
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"

// For associated bindings API
#include "mojo/public/cpp/bindings/associated_receiver.h"
#include "mojo/public/cpp/bindings/associated_remote.h"
#include "mojo/public/cpp/bindings/pending_associated_receiver.h"
#include "mojo/public/cpp/bindings/pending_associated_remote.h"
#include "mojo/public/cpp/bindings/scoped_interface_endpoint_handle.h"

#include "cc_chromium/mojo_test/mojom/mojom_test_simple.mojom.h"

#include "../cc_chromium_test.h"



// 接口实现
class ExampleImpl : public cc_chromium::mojo_test::mojom::ExampleInterface {
 public:
  void DoSomeThing(const std::string& who) override {
    printf("DoSomething() called.\n");
    std::cout << who << std::endl;
  }
};

void ClientThreadFunction(mojo::ScopedMessagePipeHandle client_pipe) {
  using namespace cc_chromium::mojo_test::mojom;
  mojo::Remote<ExampleInterface> remote;
  remote.Bind(mojo::PendingRemote<ExampleInterface>(std::move(client_pipe), 0));
  remote->DoSomeThing("this is in server");
}


void ServerThreadFunction(mojo::ScopedMessagePipeHandle server_pipe) {
  // using namespace cc_chromium::mojo_test::mojom;
  // mojo::Remote<ExampleInterface> remote;
  // remote.Bind(mojo::PendingRemote<ExampleInterface>(std::move(server_pipe)));
  // remote->DoSomeThing("this is in server");

  ExampleImpl example_impl;
  using namespace cc_chromium::mojo_test::mojom;
  mojo::Receiver<ExampleInterface> receiver(&example_impl, mojo::PendingReceiver<ExampleInterface>(std::move(server_pipe)));
}
// 主函数
TEST(CCChromiumTest, TestMojoTestSimple) {
  base::AtExitManager exit_manager;
  base::ThreadPoolInstance::CreateAndStartWithDefaultParams("MojoExample");

  mojo::core::Init();
  using namespace cc_chromium::mojo_test::mojom;
  // 创建 Mojo 管道
  // auto binding = std::make_unique<mojo::Binding<ExampleInterface>>(&example_impl, mojo::InterfaceRequest<ExampleInterface>(std::move(pipe.handle0)));
  // mojo::Receiver<ExampleInterface> receiver(&example_impl, mojo::PendingReceiver<ExampleInterface>(std::move(pipe.handle0)));
  
  // std::thread server_thread(ServerThreadFunction, std::move(pipe.handle0));
  base::Thread server_thread("ServerThread");
  server_thread.Start();
  mojo::MessagePipe pipe;
  server_thread.task_runner()->PostTask(
    FROM_HERE,
    base::BindOnce(&ServerThreadFunction, std::move(pipe.handle0))
  );
  server_thread.Stop();
}
