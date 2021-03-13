/*
  ESP-32 Resume creates a WiFi access point to host your accomplishments wherever you can supply power to the ESP-32.

  Steps:
  1. Connect to the access point "My Resume" and log in with the password "hireMePls"
  2. Hit 'em with the old elevator pitch

  Tinkerer: Moonstripe, 13 March, 2021
  Built on WiFiAccessPoint.ino by Elochukwu Ifediora (fedy0)
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

// Set these to your desired credentials.
const char *ssid = "My Resume";
const char *password = "hireMePls";

WiFiServer server(80);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");          // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // Title ASCII header
            client.println("<h2 style='font-family: monospace; white-space: pre; text-align: center'>");
            client.println("                                  _        _            ");
            client.println("                                 | |      (_)           ");
            client.println("  _ __ ___   ___   ___  _ __  ___| |_ _ __ _ _ __   ___ ");
            client.println(" | '_ ` _ &#92; / _ &#92; / _ &#92;| '_ &#92;/ __| __| '__| | '_ &#92; / _ &#92;");
            client.println(" | | | | | | (_) | (_) | | | &#92;__ &#92; |_| |  | | |_) |  __/");
            client.println(" |_| |_| |_|&#92;___/ &#92;___/|_| |_|___/&#92;__|_|  |_| .__/ &#92;___|");
            client.println("                                            |_|         ");
            client.println("</h2>");
            client.println("<br>");

            // Contact Info
            client.println("<p style='text-align: center'>-----------</p>");
            client.println("<p style='text-align: center'>#: <a href='tel:123-456-7890'>(123) 456-7890</a></p>");
            client.println("<p style='text-align: center'>@: <a href='mailto:moonstripe@protonmail.com'>moonstripe@protonmail.com</a></p>");
            client.println("<p style='text-align: center'>-----------</p>");
            client.println("<br>");

            // Resume

            // Education
            client.println("<div style='display: grid; grid-template-columns: 90px auto auto auto 90px;'>");
            client.println("<h2 style='text-align: right; grid-column-start: 2; grid-column-end: 3;'>Education<br>Qualifications</h2>");
            client.println("<div style='grid-column-start: 4; grid-column-end: 5;'>");

            // School University
            client.println("<h2>School of Life</h2>");
            client.println("<ul>");
            client.println("<li>BA in Hustlin', 'xx - 'xx</li>");
            client.println("<li>BA in Bustlin', 'xx - 'xx</li>");
            client.println("</ul>");

            client.println("</div>");
            client.println("<br>");
            client.println("<br>");

            // Professional
            client.println("<h2 style='text-align: right; grid-column-start: 2; grid-column-end: 3;'>Work Experience</h2>");
            client.println("<div style='grid-column-start: 4; grid-column-end: 5;'>");

            // Employer.com
            client.println("<h2>Employer</h2>");
            client.println("<ul>");
            client.println("<li>CEO and King, 'xx</li>");
            client.println("<li>Intern Who Gets Coffee, 'xx</li>");
            client.println("</ul>");

            // OtherEmployer.net
            client.println("<h2>Another Employer</h2>");
            client.println("<ul>");
            client.println("<li>Job Title, 'xx</li>");
            client.println("<li>A Different Job, 'xx</li>");
            client.println("</ul>");

            client.println("</div>");
            client.println("<br>");
            client.println("<br>");

            // Fun and Games
            client.println("<h2 style='text-align: right; grid-column-start: 2; grid-column-end: 3;'>Projects</h2>");
            client.println("<div style='grid-column-start: 4; grid-column-end: 5;'>");

            // ESP32 Resume
            client.println("<h2>ESP32 Resume</h2>");
            client.println("<ul>");
            client.println("<li>Lead Developer, 'xx</li>");
            client.println("</ul>");

            client.println("</div>");
            client.println("</div>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}