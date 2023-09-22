To send an HTTP message to AWS, you first must be connected to WiFi (Follow the README.md in WiFi folder). You will then need to set up 
everything on AWS following instructions below (may be outdated or missing some information)

First, go to IoT Core, and on the side bar, under Manage>All devices, click `Things`. You will then click Create Things,
Create single thing, Enter your things name, Auto-generate a new certificate, give it a policy, and create the thing. When you have
created the thing, download all certificates, and copy the contents of AmazonRootCA1.pem to certificates.h under `cert_start`, making 
each line in quotes, with a new line character at the end, and \ (Ex: "...\n" \ ). Do the same with certificate.pem.crt for `certificate_start`, and private.pem.key
for `private_start`. You can comment out the `ACCESS_KEY_USER` and `ACCESS_KEY_PASS`.

When creating a policy, go to IoT Core, under Manage>Security, click `Policies`. You will then enter a policy name, as well as actions. 
The policies used for this microcontroller were iot:Connect, iot:Subscribe, iot:Receive, and iot:Publish.

You can then go to IoT Core, under Test, click `MQTT test client`. You will then Subscribe to a topic by entering a name and clicking 
subscribe. Then, you can get the endpoint of the test client by clicking the Connection Details dropdown and copying it to HTTPURL in 
aws_http.h. You will also need to add `:<port>/topics/<your topic name>?qos=1` to the end of the defined constant. The port can be 8443, 
and topic name is what you just entered.

You do not need `esp_http_client_set_header(client, "x-api-key", '...');` for the mqtt connection, so comment that line out.

After this, in the main function, you can simply just call `post_rest_function();`.


