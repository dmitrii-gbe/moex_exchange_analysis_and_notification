#include "components/run.hpp"
#include <fmt/format.h>
#include <iostream>
#include <string_view>
#include <userver/clients/dns/component.hpp>
#include <userver/clients/http/component.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/server/handlers/tests_control.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/utils/daemon_run.hpp>

namespace sample::hello {

std::string SayHelloTo(std::string_view name) {
  if (name.empty()) {
    name = "unknown user";
  }

  return fmt::format("Hello, {}!\n", name);
}

class HelloHandler final : public userver::server::handlers::HttpHandlerBase {
public:
  // `kName` is used as the component name in static config
  static constexpr std::string_view kName = "handler-hello-sample";

  // Component is valid after construction and is able to accept requests
  using HttpHandlerBase::HttpHandlerBase;
  std::string HandleRequest(
      userver::server::http::HttpRequest &request,
      userver::server::request::RequestContext & /*request_context*/) const {
    // Setting Content-Type: text/plain in a microservice response ensures
    // the client interprets it as plain text, preventing misinterpretation or
    // errors. Without this header, the client might assume a different format,
    // such as JSON, HTML or XML, leading to potential processing issues or
    // incorrect handling of the data.
    request.GetHttpResponse().SetContentType(
        userver::http::content_type::kTextPlain);
    return SayHelloTo(request.GetArg("name"));
  }
};

} // namespace sample::hello

int main(int argc, char **argv) {
  auto component_list = userver::components::MinimalServerComponentList()
                            .Append<sample::hello::HelloHandler>(
                                std::string_view("handler-hello-sample"));
  return userver::utils::DaemonMain(argc, argv, component_list);
}
