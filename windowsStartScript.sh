
if [ -d "CurrencyConverter.app/Contents" ]; then
  cd CurrencyConverter.app/Contents/MacOS
else
  mingw32-make
  cd CurrencyConverter.app/Contents
  mv ../../userdata.txt .
  mv ../../icon.png .
  cd MacOS
fi
./CurrencyConverter