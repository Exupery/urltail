#include <iostream>
#include <string.h>
#include <unistd.h>

#include <curl/curl.h>
#include <curl/easy.h>

std::string read(const std::string url, long startAt);
int curlWrite(char* data, size_t size, size_t len, std::string* buffer);

const int POLL_INTERVAL = 3;
const int MAX_NO_DIFF   = 20;
const char USER_AGENT[] = "Mozilla/5.0 (compatible; urltail/0.1; +https://github.com/Exupery/urltail)";

int main(int argc, char* argv[]) {

  if (argc == 1) {
    std::cout << "ERROR: no URL provided" << std::endl;

    return 1;
  }

  std::string url = argv[1];
  std::cout << "Tailing " << url << std::endl;

  int noDiff = 0;
  std::string buffer = read(url, 0);
  std::cout << buffer << std::flush;

  int pos = buffer.length();

  while (noDiff < MAX_NO_DIFF) {
    sleep(POLL_INTERVAL);
    buffer = read(url, pos);
    if (buffer.length() > 0) {
      std::cout << buffer << std::flush;
      pos += buffer.length();
    } else {
      noDiff++;
    }
  }

  std::cout << "\nNo update for " << POLL_INTERVAL * MAX_NO_DIFF << " seconds. Exiting." << std::endl;

  return 0;
}

std::string read(const std::string url, long startAt) {
  std::string buffer;
  CURL* curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HEADER, 0);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, &USER_AGENT);

    curl_easy_setopt(curl, CURLOPT_RESUME_FROM, startAt);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWrite);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  } else {
    std::cout << "ERROR: unable to initialize cURL" << std::endl;
  }

  if (buffer.length() > 0) {
    buffer.pop_back();
  }
  return buffer;
}

int curlWrite(char* data, size_t size, size_t length, std::string* buffer) {
  int result = 0;

  if (buffer) {
    buffer->append(data, size * length);
    result = size * length;
  }

  return result;
}