import http.server
import socketserver

PORT = 8080

class ReuseAddrServer(socketserver.TCPServer):
    allow_reuse_address = True


def main():
    handler = http.server.SimpleHTTPRequestHandler

    httpd = ReuseAddrServer(("", PORT), handler)

    print(f"Serving at port {PORT}")
    httpd.serve_forever()


if __name__ == "__main__":
    main()
