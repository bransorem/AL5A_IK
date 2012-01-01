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

#include "joint.h"

Joint::Joint(int n, int p){
  number = n;
  pos = p;
  command = "";
  update(p);
}

// Execute movement of joint
// Send command to SSC-32
// Args:  int time (time to execute command)
void Joint::move(int time){
  if (DEBUG) { Serial.println("Moving joint"); }
  String cmd = getCommand();
  cmd = cmd + " T" + time;
  Serial.println(cmd);
  delay(time);
}

void Joint::cancel(){ Serial.println(27); } // ASCII escape

// Update position of joint in uS
// Prepare command for writing to SSC-32
// Args:  int p  (position in uS)
void Joint::update(int p){
  if (DEBUG) { Serial.println("Updating joint"); }
  pos = to_uS(p);
  command = "#" + String(number) + " P" + String(pos);
  delay(10);
}
