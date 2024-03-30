if [ -d "CurrencyConverter.app/Contents" ]; then
  cd CurrencyConverter.app/Contents/MacOS
else
  cmake .
  make
  cd CurrencyConverter.app/Contents
  mv ../../userdata.txt .
  cd MacOS
  mv ../../../icon.png .
fi
./CurrencyConverter