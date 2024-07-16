;; Auto-generated. Do not edit!


(when (boundp 'robot_control::machine_status)
  (if (not (find-package "ROBOT_CONTROL"))
    (make-package "ROBOT_CONTROL"))
  (shadow 'machine_status (find-package "ROBOT_CONTROL")))
(unless (find-package "ROBOT_CONTROL::MACHINE_STATUS")
  (make-package "ROBOT_CONTROL::MACHINE_STATUS"))

(in-package "ROS")
;;//! \htmlinclude machine_status.msg.html


(defclass robot_control::machine_status
  :super ros::object
  :slots (_Roller _Mode _KeepOrNot _PlaceOrNot _RobotStatus ))

(defmethod robot_control::machine_status
  (:init
   (&key
    ((:Roller __Roller) 0)
    ((:Mode __Mode) 0)
    ((:KeepOrNot __KeepOrNot) 0)
    ((:PlaceOrNot __PlaceOrNot) 0)
    ((:RobotStatus __RobotStatus) "")
    )
   (send-super :init)
   (setq _Roller (round __Roller))
   (setq _Mode (round __Mode))
   (setq _KeepOrNot (round __KeepOrNot))
   (setq _PlaceOrNot (round __PlaceOrNot))
   (setq _RobotStatus (string __RobotStatus))
   self)
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

(setf (get robot_control::machine_status :md5sum-) "358fea0a2efe9c679e20648d6430914a")
(setf (get robot_control::machine_status :datatype-) "robot_control/machine_status")
(setf (get robot_control::machine_status :definition-)
      "uint8 Roller
uint8 Mode
uint8 KeepOrNot
uint8 PlaceOrNot
string RobotStatus

")



(provide :robot_control/machine_status "358fea0a2efe9c679e20648d6430914a")


