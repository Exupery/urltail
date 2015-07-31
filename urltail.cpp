#include <iostream>
#include <string.h>
#include <unistd.h>

#include <curl/curl.h>
#include <curl/easy.h>

std::string read(const std::string url);
int curlWrite(char* data, size_t size, size_t len, std::string* buffer);

const char USER_AGENT[] = "Mozilla/5.0 (compatible; urltail/0.1; +https://github.com/Exupery/urltail)";

int main(int argc, char* argv[]) {

  if (argc == 1) {
    std::cout << "ERROR: no URL provided" << std::endl;

    return 1;
  }

  std::cout << "Tailing " << argv[1] << std::endl;

  std::string previous = read(argv[1]);
  std::cout << previous << std::endl;   // TODO DELME

  std::string current;

  while (true) {
    current = read(argv[1]);
    // TODO DIFF CURRENT VS PREVIOUS AND APPEND DIFF TO OUTPUT
    std::cout << current << std::endl;  // TODO DELME
    sleep(5);
  }

  return 0;
}

std::string read(const std::string url) {
  std::string buffer;
  CURL* curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HEADER, 0);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, &USER_AGENT);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWrite);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  } else {
    std::cout << "ERROR: unable to initialize cURL" << std::endl;
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