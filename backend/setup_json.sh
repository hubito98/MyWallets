git clone https://github.com/nlohmann/json.git
cd json && git checkout e9f88c2fad4b910b90262019df72181c14a0370f && cd ..
mv json/single_include/nlohmann .
rm -rf json