# mqtt


## mosqitto
- MQTTプロトコルを利用するためのオープンソースブローカー
```
https://mosquitto.org/
```

## ターミナルで確認
- インストール

```
sudo add-apt-repository ppa:mosquitto-dev/mosquitto-ppa
sudo apt-get update
sudo apt-get install mosquitto-clients
sudo apt-get install mosquitto
```

- 三つターミナルを開く。（pub,sub,broker用）

- broker
```
mosquitto
```

- sub
```
mosquitto_sub -d -t test
```

- pub
```
mosquitto_pub -d -t test -m "Hello world!"
```




## プログラムで



## paho
- MQTT

- Paho-Cのインストール
```
git clone https://github.com/eclipse/paho.mqtt.c.git
cd paho.mqtt.c
#git checkout v1.3.8
cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON \
    -DPAHO_WITH_SSL=ON -DPAHO_HIGH_PERFORMANCE=ON
sudo cmake --build build/ --target install
sudo ldconfig
```

- Paho C++のインストール
```
git clone https://github.com/eclipse/paho.mqtt.cpp
cd paho.mqtt.cpp

cmake -Bbuild -H. -DPAHO_BUILD_STATIC=ON \
    -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_SAMPLES=TRUE
sudo cmake --build build/ --target install
sudo ldconfig
```



## error

- opensslのインストールがない

```
CMake Error at /usr/share/cmake-3.16/Modules/FindPackageHandleStandardArgs.cmake:146 (message):
  Could NOT find OpenSSL, try to set the path to OpenSSL root folder in the
  system variable OPENSSL_ROOT_DIR (missing: OPENSSL_CRYPTO_LIBRARY
  OPENSSL_INCLUDE_DIR)
Call Stack (most recent call first):
  /usr/share/cmake-3.16/Modules/FindPackageHandleStandardArgs.cmake:393 (_FPHSA_FAILURE_MESSAGE)
  /usr/share/cmake-3.16/Modules/FindOpenSSL.cmake:447 (find_package_handle_standard_args)
  CMakeLists.txt:55 (find_package)

```

- cpp側のcmakeでもエラー

```
  naka@DESKTOP-0ERPVKH:~/work/code_test/C++_/mqtt_paho/mqtt_paho_cpp/paho.mqtt.cpp$ cmake .
```

```
-- Found OpenSSL: /usr/lib/x86_64-linux-gnu/libcrypto.so (found version "1.1.1f")  
CMake Error at CMakeLists.txt:100 (find_package):
  By not providing "Findeclipse-paho-mqtt-c.cmake" in CMAKE_MODULE_PATH this
  project has asked CMake to find a package configuration file provided by
  "eclipse-paho-mqtt-c", but CMake did not find one.

  Could not find a package configuration file provided by
  "eclipse-paho-mqtt-c" with any of the following names:

    eclipse-paho-mqtt-cConfig.cmake
    eclipse-paho-mqtt-c-config.cmake

  Add the installation prefix of "eclipse-paho-mqtt-c" to CMAKE_PREFIX_PATH
  or set "eclipse-paho-mqtt-c_DIR" to a directory containing one of the above
  files.  If "eclipse-paho-mqtt-c" provides a separate development package or
  SDK, be sure it has been installed.


-- Configuring incomplete, errors occurred!
See also "/home/naka/work/code_test/C++_/mqtt_paho/mqtt_paho_cpp/paho.mqtt.cpp/CMakeFiles/CMakeOutput.log".

```



## REFERENCE
ubuntuでMQTTブローカー「mosquitto」のインストール方法  
https://qiita.com/rui0930/items/40bd5a1cfd3422206ad3   

UbuntuにMosquittoをインストールしてMQTTブローカーを構築   
https://qiita.com/kyoro353/items/b862257086fca02d3635  




Raspberry Pi4にPaho C++をインストール  
https://zenn.dev/fate_shelled/scraps/9c2e60411bcfd7