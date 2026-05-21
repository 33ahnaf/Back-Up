from http.server import HTTPServer, BaseHTTPRequestHandler
import cgi
import time

class MockESP32Handler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/':
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            with open('HotPink.html', 'rb') as file:
                self.wfile.write(file.read())
        elif self.path == '/disconnect':
            print("Disconnected! 🛑")
            self.send_response(200)
            self.end_headers()

    def do_POST(self):
        if self.path == '/upload':
            # Get the total size of the upload
            content_length = int(self.headers['Content-Length'])
        
            # Define simulation speed: 0.5 MB per second
            chunk_size = 64 * 1024  # 64KB chunks
            bytes_read = 0
        
            print(f"Receiving {content_length / 1024 / 1024:.2f} MiB...")

            while bytes_read < content_length:
                # Read a small piece of the stream
                remaining = content_length - bytes_read
                chunk = self.rfile.read(min(chunk_size, remaining))
                bytes_read += len(chunk)
            
                # Artificial Delay: adjust this to change speed
                time.sleep(0.05) 
            
            self.send_response(200)
            self.end_headers()
            self.wfile.write(b"OK")
            print("Upload finished! ✅")

print("Serving on http://localhost:8000")
HTTPServer(('localhost', 8000), MockESP32Handler).serve_forever()
