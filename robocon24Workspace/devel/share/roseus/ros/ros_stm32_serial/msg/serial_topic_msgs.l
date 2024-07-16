;; Auto-generated. Do not edit!


(when (boundp 'ros_stm32_serial::serial_topic_msgs)
  (if (not (find-package "ROS_STM32_SERIAL"))
    (make-package "ROS_STM32_SERIAL"))
  (shadow 'serial_topic_msgs (find-package "ROS_STM32_SERIAL")))
(unless (find-package "ROS_STM32_SERIAL::SERIAL_TOPIC_MSGS")
  (make-package "ROS_STM32_SERIAL::SERIAL_TOPIC_MSGS"))

(in-package "ROS")
;;//! \htmlinclude serial_topic_msgs.msg.html


(defclass ros_stm32_serial::serial_topic_msgs
  :super ros::object
  :slots (_flag _status _linearX _linearY _angularZ _LaserFront _LaserL _LaserR _LaserRear _Roller _Mode _KeepOrNot _PlaceOrNot _RobotStatus ))

(defmethod ros_stm32_serial::serial_topic_msgs
  (:init
   (&key
    ((:flag __flag) 0.0)
    ((:status __status) 0.0)
    ((:linearX __linearX) 0.0)
    ((:linearY __linearY) 0.0)
    ((:angularZ __angularZ) 0.0)
    ((:LaserFront __LaserFront) 0)
    ((:LaserL __LaserL) 0)
    ((:LaserR __LaserR) 0)
    ((:LaserRear __LaserRear) 0)
    ((:Roller __Roller) 0)
    ((:Mode __Mode) 0)
    ((:KeepOrNot __KeepOrNot) 0)
    ((:PlaceOrNot __PlaceOrNot) 0)
    ((:RobotStatus __RobotStatus) "")
    )
   (send-super :init)
   (setq _flag (float __flag))
   (setq _status (float __status))
   (setq _linearX (float __linearX))
   (setq _linearY (float __linearY))
   (setq _angularZ (float __angularZ))
   (setq _LaserFront (round __LaserFront))
   (setq _LaserL (round __LaserL))
   (setq _LaserR (round __LaserR))
   (setq _LaserRear (round __LaserRear))
   (setq _Roller (round __Roller))
   (setq _Mode (round __Mode))
   (setq _KeepOrNot (round __KeepOrNot))
   (setq _PlaceOrNot (round __PlaceOrNot))
   (setq _RobotStatus (string __RobotStatus))
   self)
  (:flag
   (&optional __flag)
   (if __flag (setq _flag __flag)) _flag)
  (:status
   (&optional __status)
   (if __status (setq _status __status)) _status)
  (:linearX
   (&optional __linearX)
   (if __linearX (setq _linearX __linearX)) _linearX)
  (:linearY
   (&optional __linearY)
   (if __linearY (setq _linearY __linearY)) _linearY)
  (:angularZ
   (&optional __angularZ)
   (if __angularZ (setq _angularZ __angularZ)) _angularZ)
  (:LaserFront
   (&optional __LaserFront)
   (if __LaserFront (setq _LaserFront __LaserFront)) _LaserFront)
  (:LaserL
   (&optional __LaserL)
   (if __LaserL (setq _LaserL __LaserL)) _LaserL)
  (:LaserR
   (&optional __LaserR)
   (if __LaserR (setq _LaserR __LaserR)) _LaserR)
  (:LaserRear
   (&optional __LaserRear)
   (if __LaserRear (setq _LaserRear __LaserRear)) _LaserRear)
  (:Roller
   (&optional __Roller)
   (if __Roller (setq _Roller __Roller)) _Roller)
  (:Mode
   (&optional __Mode)
   (if __Mode (setq _Mode __Mode)) _Mode)
  (:KeepOrNot
   (&optional __KeepOrNot)
   (if __KeepOrNot (setq _KeepOrNot __KeepOrNot)) _KeepOrNot)
  (:PlaceOrNot
   (&optional __PlaceOrNot)
   (if __PlaceOrNot (setq _PlaceOrNot __PlaceOrNot)) _PlaceOrNot)
  (:RobotStatus
   (&optional __RobotStatus)
   (if __RobotStatus (setq _RobotStatus __RobotStatus)) _RobotStatus)
  (:serialization-length
   ()
   (+
    ;; float64 _flag
    8
    ;; float64 _status
    8
    ;; float64 _linearX
    8
    ;; float64 _linearY
    8
    ;; float64 _angularZ
    8
    ;; int32 _LaserFront
    4
    ;; int32 _LaserL
    4
    ;; int32 _LaserR
    4
    ;; int32 _LaserRear
    4
    ;; uint8 _Roller
    1
    ;; uint8 _Mode
    1
    ;; uint8 _KeepOrNot
    1
    ;; uint8 _PlaceOrNot
    1
    ;; string _RobotStatus
    4 (length _RobotStatus)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _flag
       (sys::poke _flag (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _status
       (sys::poke _status (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _linearX
       (sys::poke _linearX (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _linearY
       (sys::poke _linearY (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _angularZ
       (sys::poke _angularZ (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int32 _LaserFront
       (write-long _LaserFront s)
     ;; int32 _LaserL
       (write-long _LaserL s)
     ;; int32 _LaserR
       (write-long _LaserR s)
     ;; int32 _LaserRear
       (write-long _LaserRear s)
     ;; uint8 _Roller
       (write-byte _Roller s)
     ;; uint8 _Mode
       (write-byte _Mode s)
     ;; uint8 _KeepOrNot
       (write-byte _KeepOrNot s)
     ;; uint8 _PlaceOrNot
       (write-byte _PlaceOrNot s)
     ;; string _RobotStatus
       (write-long (length _RobotStatus) s) (princ _RobotStatus s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _flag
     (setq _flag (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _status
     (setq _status (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _linearX
     (setq _linearX (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _linearY
     (setq _linearY (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _angularZ
     (setq _angularZ (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int32 _LaserFront
     (setq _LaserFront (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _LaserL
     (setq _LaserL (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _LaserR
     (setq _LaserR (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _LaserRear
     (setq _LaserRear (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint8 _Roller
     (setq _Roller (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _Mode
     (setq _Mode (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _KeepOrNot
     (setq _KeepOrNot (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _PlaceOrNot
     (setq _PlaceOrNot (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; string _RobotStatus
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _RobotStatus (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get ros_stm32_serial::serial_topic_msgs :md5sum-) "d5bec99ac5726ba6e665cc5e4980b15b")
(setf (get ros_stm32_serial::serial_topic_msgs :datatype-) "ros_stm32_serial/serial_topic_msgs")
(setf (get ros_stm32_serial::serial_topic_msgs :definition-)
      "float64 flag
float64 status
float64 linearX
float64 linearY
float64 angularZ
int32 LaserFront
int32 LaserL
int32 LaserR
int32 LaserRear
uint8 Roller
uint8 Mode
uint8 KeepOrNot
uint8 PlaceOrNot
string RobotStatus

")



(provide :ros_stm32_serial/serial_topic_msgs "d5bec99ac5726ba6e665cc5e4980b15b")


