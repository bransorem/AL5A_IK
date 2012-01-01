/* Copyright (C) 2011 Brannen Sorem. All rights reserved.

This software may be distributed and modified under the terms of the GNU
General Public License version 2 (GPL2) as published by the Free Software
Foundation and appearing in the file GPL2.TXT included in the packaging of
this file. Please note that GPL2 Section 2[b] requires that all works based
on this software must also be made publicly available under the terms of
the GPL2 ("Copyleft").

Contact information
-------------------

Author   :  Brannen Sorem
Web      :  http://www.bransorem.com
e-mail   :  contact@bransorem.com
*/

#include "arm.h"

Arm::Arm() {
  base.setNumber(0);
  base.setPosition(90);
  
  shoulder.setNumber(1);
  shoulder.setPosition(0);
  
  elbow.setNumber(2);
  elbow.setPosition(0);
  
  wrist.setNumber(3);
  wrist.setPosition(0);
  
  wrist_rotate.setNumber(4);
  wrist_rotate.setPosition(0);
  
  gripper.setNumber(5);
  gripper.setPosition(0);
  
  array[0] = &base;
  array[1] = &shoulder;
  array[2] = &elbow;
  array[3] = &wrist;
  array[4] = &wrist_rotate;
  array[5] = &gripper;
           
  arm.setJoints(array, 6);
  if (DEBUG) { Serial.println("Initialized array"); }
}

void Arm::move(float b, float s, float e, float w, float wr, float g, int t){
  
  if (DEBUG) { Serial.println("Moving arm"); }
  
  // Move each servo manually
  if (DEBUG) { Serial.println("Update base"); }
  base.update(b);
  if (DEBUG) { Serial.println("Update shoulder"); }
  shoulder.update(s);
  if (DEBUG) { Serial.println("Update elbow"); }
  elbow.update(e);
  if (DEBUG) { Serial.println("Update wrist"); }
  wrist.update(w);
  if (DEBUG) { Serial.println("Update wrist-rotate"); }
  wrist_rotate.update(wr);
  if (DEBUG) { Serial.println("Update gripper"); }
  gripper.update(g);
  arm.update();
  arm.move(t);
}


/* INVERSE KINEMATICS
   Algebraic solution based on PUMA 560 inverse manipulator kinematics.
   Refer to Section 4.7 (Examples of Inverse Manipulator Kinematics) of
   Introduction to Robotics, 3rd ed. by John Craig (page 117).
*/
void Arm::move(float x, float y, float z, int t){
  if (DEBUG) { Serial.println("Preparing IK"); }
  // base height, humerus, ulna, gripper
  float theta1, theta2, theta3, theta4, theta5, theta6;
  
  theta1 = atan2(y, x) - atan2(d3, sqrt(sq(x) + sq(y) - sq(d3)));
  float K = (2*sq(x) + sq(y) - sq(a2) - sq(a3) - sq(d3) - sq(d4))/(2*a2);
  theta3 = atan2(a3, d4) - atan2(K, sqrt(sq(a3) + sq(d4) - sq(K)));
  float s1 = sin(theta1);
  float s3 = sin(theta3);
  float c1 = cos(theta1);
  float c3 = cos(theta3);
  float theta23 = atan2((-a3-a2*c3)*z - (c1*x + s1*y)*(d4 - a2*s3), 
                  (a2*s3 - d4)*z - (a3 + a2*c3)*(c1*x + s1*y));
  theta2 = theta23 - theta3;
  float s23 = ((-a3 - a2*c3)*z + (c1*x + s1*y)*(a2*s3 - d4))  /  (sq(z) + sq((c1*x + s1*y)));
  float c23 = ((a2*s3 - d4)*z - (a3 + a2*c3)*(c1*x + s1*y))  /  (sq(z) + sq(c1*x + s1*y));
  // theta4 = atan2(-r13*s1 + r23*c1, -r13*c1*c23 - r23*s1*c23 + r33*s23);
  theta4 = -theta2 - theta3;
  
  // Convert from radians to degrees
  theta1 *= 57.2957795;
  theta2 *= 57.2957795;
  theta3 *= 57.2957795;
  theta4 *= 57.2957795;
  
  if (DEBUG) { Serial.println("Update base"); }
  base.update(theta1);
  if (DEBUG) { Serial.println("Update shoulder"); }
  shoulder.update(theta2);
  if (DEBUG) { Serial.println("Update elbow"); }
  elbow.update(theta3);
  if (DEBUG) { Serial.println("Update wrist"); }
  wrist.update(theta4);
  
  if (DEBUG) { Serial.println("Calculated IK"); }
  
  arm.update();
  arm.move(t);
}

void Arm::cancel(){
  arm.cancel();
}


void Arm::test(){
  //move(90,0,-50,45,-45,0,1000);
  //move(0,90,50,-45,45,90,1000);
}
