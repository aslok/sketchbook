#!/usr/bin/env php
<?php

const WIDTH = 84, HEIGHT = 48;

$imgs_cnt = 0;
$out = "{\n";
foreach (glob('./img/*') as $img_path) {
  $imgs_cnt++;
  $im = false;
  //echo $img_path, "\n";
  switch (exif_imagetype($img_path)){
    case IMAGETYPE_JPEG:
      $im = imagecreatefromjpeg($img_path);
      break;
    case IMAGETYPE_GIF:
      $im = imagecreatefromgif($img_path);
      break;
    case IMAGETYPE_PNG:
      $im = imagecreatefrompng($img_path);
      break;
    case IMAGETYPE_BMP:
      $im = imagecreatefrombmp($img_path);
      break;
    default:
      //echo 'Continue', "\n";
      continue;
  }
  list($width, $height) = getimagesize($img_path);
  if ($width != WIDTH || $height != HEIGHT){
    //echo 'Unsupported size', "\n";
    continue;
  }
  if (!$im){
    //echo 'Error on open', "\n";
    continue;
  }
  
  $out .= "{\n";
  $count = 0;
  for ($f = 0; $f < HEIGHT; $f++){
    $out_pos = 0;
    for ($f2 = 0; $f2 < WIDTH; $f2++){
      if (!$out_pos){
        $out .= 'B';
        $count++;
      }
      $rgb = imagecolorsforindex($im, imagecolorat($im, $f2, $f));
      $out .= ($rgb['red'] == 255 && $rgb['green'] == 255 && $rgb['blue'] == 255) ? 1 : 0;
      $out_pos++;
      if ($out_pos == 8){
        $out .= ',';
        $out_pos = 0;
      }
    }
    while ($out_pos && $out_pos < 8){
      $out .= '0';
      $out_pos++;
    }
    $out .= ",\n";
  }
  $out .= "},\n";
}
$out = '#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"

// D3 - LCD 1 - reset (RST)
// D4 - LCD 2 - chip select (CS)
// D5 - LCD 3 - Data/Command select (D/C)
// D6 - LCD 4 - Serial data out (DIN)
// D7 - LCD 5 - Serial clock out (SCLK)
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);

const byte ms = 700;
const byte imgs_cnt = 32;
const byte PROGMEM imgs[][528] = ' . $out . "};

byte current = 0;

void setup() {
  display.begin();
  display.setContrast(51);
}

void loop() {
  if (current == imgs_cnt){
    current = 0;
  }
  display.drawBitmap(0, 0, imgs[current++], 84, 48, WHITE, BLACK);
  display.display();
  delay(ms);
}
\n";
echo $out;
exit;
