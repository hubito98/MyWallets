git clone https://github.com/meltwater/served.git
cd served && git checkout 2eb36b83fa69330900ae58ef41d12b5f7abc138c && cd ..
mkdir served.build && cd served.build
cmake ../served && make
make install