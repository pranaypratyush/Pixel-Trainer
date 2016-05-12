# Pixel Trainer

Pixel Trainer is a software used to label each pixel of images like bouy.Labeling can be done soomthly by draging the mouse.The labels are :-

 -  0  for Yellow  
 -  1 for  Green
 -  2 for Red
 - -1 : Default
 
For each image a text file is generated containing the labelling and HSV value of each Pixel

### Instruction
In labelling involves pressing a key and left clicking and dragging the mouse 
* For labelling Yellow press Crtl key 
* For labelling Green press Shift key 
* For labelling Red press Alt key

The brush size or labelling area can be changed using the given trackbar.
To Save or Clear ,use the brush icon in the taskbar.

The `main_static` file is the "statified" version of the `main` binary. It has all dynamic linkages statified and therefore would run on systems without 'opencv-3.1.0' installed. This was done using `ErmineLight`.
