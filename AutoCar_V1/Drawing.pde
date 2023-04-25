
void drawStuff(){
  background(230);
   pushMatrix();
   translate(width/2, height/4);
   rotate(angleX);
   fill(120,0,0);
   rectMode(CENTER);
   rect(0,0,200,100);   
   popMatrix();
   pushMatrix();
   translate(width/2, 3*height/4);
   rotate(angleY);
   fill(0,0,120);
   rectMode(CENTER);
   rect(0,0,200,100);   
   popMatrix();
   
   pushMatrix();
   translate(width/2, height/2);
   rotate(-angleZ);
   fill(0,120,0);
   rectMode(CENTER);
   rect(0,0,100,50);   
   popMatrix();
  rect(350,30,40,distance);
}
