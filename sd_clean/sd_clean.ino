#include "SPI.h"
#include "SD.h"

Sd2Card card;
SdVolume volume;
SdFile root;

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  if (!SD.begin(4)) {
    Serial.println("Error");
  }
  Serial.println("Done");
  root = SD.open("/");
  deleteDirectory(root);


  // Вариант 1: Выбираем рут
  //if (!volume.init(card)) {
  //  Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
  //  return;
  //}
  //Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  //root.openRoot(volume);
  // list all files in the card with date and size
  //root.ls(LS_R | LS_DATE | LS_SIZE);
  //uint32_t volumesize;
  //volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  //volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  //volumesize *= 512;                            // SD card blocks are always 512 bytes
  //volumesize = volumesize / 1024 / 1024;
  //Serial.print("Volume size (Mbytes): ");
  //Serial.println(volumesize);

  // Вариант 2: Открываем путь
  //if (!SD.begin(4)) {
  //  Serial.println("Error");
  //}
  //if (SD.exists("example.txt")) {
  //Serial.println("example.txt exists.");
  //Serial.println("Creating example.txt...");
  //myFile = SD.open("example.txt", FILE_WRITE);
  // make a string for assembling the data to log:
  //String dataString = "";
  // read three sensors and append to the string:
  //for (int analogPin = 0; analogPin < 3; analogPin++) {
  //  int sensor = analogRead(analogPin);
  //  dataString += String(sensor);
  //  if (analogPin < 2) {
  //    dataString += ",";
  //  }
  //}
  //Serial.print("Writing to test.txt...");
  //myFile.println(dataString);
  //myFile.close();
  //myFile = SD.open("test.txt");
  // read from the file until there's nothing else in it:
  //while (myFile.available()) {
  //  Serial.write(myFile.read());
  //}
  //SD.remove("example.txt");



}
void loop() {}

void deleteDirectory(File dir) {
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    // Serial.print(entry.name());
    if (entry.isDirectory()) {
      deleteDirectory(entry);
    } else {
      Serial.println(entry.name());
    }
    entry.close();
  }
}

