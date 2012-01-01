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

#include "joints.h"


// Establish the joints that will be used with this joint set
// Args:  Joint* array_of_joints[],  int length_of_array
void Joints::setJoints(Joint* jointset[], int len){
  _length = len;
  for (int i=0; i < len; i++){
    appendJoint(jointset[i]);
  }
}

// Add a joint to this joint set
// Args:  Joint* joint
void Joints::appendJoint(Joint* joint){
  int len = _length;
  // can only have 32 joints with the SSC-32
  if (len <= 32){
    joints[len] = joint;
    len++;
    _length = len;
  }
  else {
    // error, too many joints
  }
}

// Remove a joint from the joint set
// 'pops' off last joint
void Joints::removeJoint(){
  int len = _length;
  // are there any joints in the set?
  if (len > 0){
    joints[len] = 0;
    len--;
    _length = len;
  }
  else {
    // error, no joints in array
  }
}

// Set the command for writing to SSC-32 board
void Joints::update(){
  if (DEBUG) { Serial.println("Updating joints"); }
  String cmd = "";
  //Serial.println("Length: " + String(_length));
  for (int i=0; i < _length; i++){
    Joint j = *joints[i];
    cmd = cmd + j.getCommand() + ' ';
  }
  command = cmd;
}


void Joints::cancel(){  Serial.println(27); } // ASCII escape


// Execute the command prepared for the SSC-32 (with given time)
// Args:  int time_to_execute_command
void Joints::move(int time){
  if (DEBUG) { Serial.println("Moving joints"); }
  String cmd = getCommand();
  cmd = cmd + "T" + String(time);
  Serial.println(cmd);
  delay(time);
}
