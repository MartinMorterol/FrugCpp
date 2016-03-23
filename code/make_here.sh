nom=demoFrug
mkdir -p build
cd build;
cmake ..;
make;
mv $nom ../$nom
cd ..
