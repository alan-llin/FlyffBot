#pragma once
#ifndef FLYFF_H
#define FLYFF_H

class flyff {

	private:
		void* _handle;
		unsigned long _base_addr;
		unsigned long _select_addr;
		unsigned long _maxInView_addr;
		unsigned long _targetBase_addr;
		unsigned long _char_addr;

	public:

		flyff(void *handle, unsigned long base_addr);

		struct targetInfo
		{
			unsigned long base; //offset-0
			float x, y, z;      //offset-164
			float hyp;          //comes from calc
			unsigned long lvl;  //offset-6F4 
			unsigned long hp;   //offset-718
			char name[255];     //offset-1BA0 , pet offset-728
		};

		void select(unsigned long target);
		unsigned long getSelect();
		unsigned long getMe();
		float getHyp(targetInfo ti);
		unsigned long getHp();
		targetInfo getClosestTargetInView();

};

#endif // !FLYFF_H
