#!/usr/bin/env php
<?php

const WIDTH = 84, HEIGHT = 40;
const FRAMES_DIVIDER = 4;

// rm -rf img/ ; mkdir img && convert -coalesce IMG_0081.GIF img/%03d.png && convert -crop 220x105+135+85 img/???.png -resize 84x40 img/out%03d.png && convert img/out* -monochrome img/%03d.png && rm img/out* && ./convert.php
// rm -rf img/ ; mkdir img && convert -coalesce IMG_0081.GIF img/%03d.png && convert -crop 220x105+135+85 img/???.png -resize 84x40 img/out%03d.png && convert img/out* -monochrome -splice 0x8 img/%03d.png && rm img/out* && ./convert.php

$imgs_cnt = 0;
$files_cnt = 0;
$out = "{\n";
foreach (glob('./img/*') as $img_path) {
  if ($files_cnt++ % FRAMES_DIVIDER){
	continue;
  }
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
      $out .= ($rgb['red'] == 255 && $rgb['green'] == 255 && $rgb['blue'] == 255) ? 0 : 1;
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
$out = '#ifndef IMGS_H
#define IMGS_H

#include "Arduino.h"

const byte imgs_cnt = ' . $imgs_cnt . ';
const byte PROGMEM imgs[][' . (ceil(WIDTH / 8) * HEIGHT) . '] = ' . $out . '};

#endif // IMGS_H
' . "\n";
file_put_contents('imgs.c', $out);
exit;
