# oatpp-mcp

Anthropic’s Model Context Protocol implementation for Oat++

Read more:
- [About Oat++](https://oatpp.io/)
- [Oat++ Repository](https://github.com/oatpp/oatpp)
- [Model Context Protocol](https://www.anthropic.com/news/model-context-protocol)

## Supported features

### Transport

- STDIO
- HTTP SSE

### Server features

- [Prompts](https://spec.modelcontextprotocol.io/specification/server/prompts/)
- [Tools](https://spec.modelcontextprotocol.io/specification/server/tools/)

## Build And Install

### Pre Requirements

- Install the main [oatpp](https://github.com/oatpp/oatpp) module

### Install module

- Clone this repository.
- In the root of the repository run:
   ```bash
   mkdir build && cd build
   cmake ..
   make install
   ```
  
## Examples

Find working example in tests `/test/oatpp-mcp/app/ServerTest.cpp`

### Serve via STDIO

**Note:** make sure to redirect oatpp logging to a different stream - ex.: to file by providing custom Logger.

```cpp
  /* Create MCP server */
  oatpp::mcp::Server server;

  /* Add prompts */
  server.addPrompt(std::make_shared<prompts::CodeReview>());

  /* Add tools */
  server.addTool(std::make_shared<tools::Logger>());

  /* Run server */
  server.stdioListen(); 
```

### Serve via SSE

```cpp
  /* Create MCP server */
  oatpp::mcp::Server server;

  /* Add prompts */
  server.addPrompt(std::make_shared<prompts::CodeReview>());

  /* Add tools */
  server.addTool(std::make_shared<tools::Logger>());

  /* Add SSE controller to your HTTP server router */
  router->addController(server.getSseController());
```

