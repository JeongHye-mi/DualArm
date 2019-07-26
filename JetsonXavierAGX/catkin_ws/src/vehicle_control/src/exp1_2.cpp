#include "ros/ros.h"
#include "vehicle_control/commendMsg.h"
#include <math.h>


int main(int argc, char **argv)
{
  ros::init(argc,argv,"cmd_publisher2");
  ros::NodeHandle nh;

  ros::Publisher cmd_pub=nh.advertise<vehicle_control::commendMsg>("/ns1/cmd_msg",100); //100 que size//

  int hz1 = 30;
//  int hz2 = 20; // 0.30m/s

  ros::Rate loop_rate(hz1); // Setting 50 Hz //


  int N=200; //


  double xd=0;
  double yd=0;
  double phid;

  double x1 = -0.6;
  double y1 = 0;

  double x2 = x1;
  double y2 = -0.6;

  double x3 = 0.5;
  double y3 = y2;

  double x4 = x3;
  double y4 = 0.5;

  double x5 = x2;
  double y5 = y4;


  int n=1;

  int rotation_index = 1;

  int i=0;
  int j=0;
  int k=0;

  int index=1;


  while(ros::ok())
  {


    vehicle_control::commendMsg cmd_msg;

    // Trajectory : Rectangular


//     From point 1 to point 2
    if(index ==1){
    xd = (double) x1*i/N;
    yd = (double) y1*i/N;

//    Orientation
    phid = (double) 3.141592*i/N/2.0+(double)3.141592*(rotation_index-1)/2;

    i++;
        if(i>N){
            i=0;
            index = 2;
            rotation_index++;
            ros::Duration(1).sleep();
        }

    }

//     From point 2 to point 3
    if(index ==2){
    xd = (double) (x2-x1)*i/N+x1;
    yd = (double) (y2-y1)*i/N+y1;
    i++;

//    Orientation
    phid = (double) 3.141592*i/N/2.0+(double)3.141592*(rotation_index-1)/2;

        if(i>N){
            i=0;
            index = 3;
            rotation_index++;
            ros::Duration(1).sleep();
            }

    }

//     From point 3 to point 4
    if(index ==3){
    xd = (double)(x3-x2)*i/N+x2;
    yd = (double)(y3-y2)*i/N+y2;
    i++;

//    Orientation
    phid = (double) 3.141592*i/N/2.0+(double)3.141592*(rotation_index-1)/2;

        if(i>N){
            i=0;
            index = 4;
            rotation_index++;
            ros::Duration(1).sleep();
        }
    }


//     From point 4 to point 1
    if(index ==4){
    xd = (double)(x4-x3)*i/N+x3;
    yd = (double)(y4-y3)*i/N+y3;
    i++;

//    Orientation
    phid = (double) 3.141592*i/N/2.0+(double)3.141592*(rotation_index-1)/2;

        if(i>N){
            i=0;
            index = 5;
            rotation_index++;
            ros::Duration(1).sleep();
        }
    }

    if(index ==5){
    xd = (x5-x4)*i/N+x4;
    yd = (y5-y4)*i/N+y4;
    i++;

//    Orientation
    phid = (double) 3.141592*i/N/2.0+(double)3.141592*(rotation_index-1)/2;

        if(i>N){
            i=0;
            index = 6;
            rotation_index++;
            ros::Duration(0.5).sleep();
        }
    }

    if(index == 6){
    xd = (x2-x5)*i/N+x5;
    yd = (y2-y5)*i/N+y5;
    i++;

//    Orientation
    phid = (double) 3.141592*i/N/2.0+(double)3.141592*(rotation_index-1)/2;

        if(i>N){
            i=0;
            index = 3;
            rotation_index++;
            n++;
        }
    }

    if(n>2){
    xd=0;
    yd=0;
    index = 7;
    phid = (double) 3.141592*i/N/2.0+(double)3.141592*(rotation_index-3)/2;
    }


    cmd_msg.xd = xd;
    cmd_msg.yd = yd;
    cmd_msg.phid = phid;


    cmd_pub.publish(cmd_msg);


    ROS_INFO("%d" ,n);
    ROS_INFO("Pub Msg : %lf %lf %lf",cmd_msg.xd,cmd_msg.yd,cmd_msg.phid);

    loop_rate.sleep();

  }

  return 0;

}

