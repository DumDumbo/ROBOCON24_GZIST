;; Auto-generated. Do not edit!


(when (boundp 'robot_control::msg4pid)
  (if (not (find-package "ROBOT_CONTROL"))
    (make-package "ROBOT_CONTROL"))
  (shadow 'msg4pid (find-package "ROBOT_CONTROL")))
(unless (find-package "ROBOT_CONTROL::MSG4PID")
  (make-package "ROBOT_CONTROL::MSG4PID"))

(in-package "ROS")
;;//! \htmlinclude msg4pid.msg.html


(defclass robot_control::msg4pid
  :super ros::object
  :slots (_kp _ki _kd _feedback _setpoint ))

(defmethod robot_control::msg4pid
  (:init
   (&key
    ((:kp __kp) 0.0)
    ((:ki __ki) 0.0)
    ((:kd __kd) 0.0)
    ((:feedback __feedback) 0.0)
    ((:setpoint __setpoint) 0.0)
    )
   (send-super :init)
   (setq _kp (float __kp))
   (setq _ki (float __ki))
   (setq _kd (float __kd))
   (setq _feedback (float __feedback))
   (setq _setpoint (float __setpoint))
   self)
  (:kp
   (&optional __kp)
   (if __kp (setq _kp __kp)) _kp)
  (:ki
   (&optional __ki)
   (if __ki (setq _ki __ki)) _ki)
  (:kd
   (&optional __kd)
   (if __kd (setq _kd __kd)) _kd)
  (:feedback
   (&optional __feedback)
   (if __feedback (setq _feedback __feedback)) _feedback)
  (:setpoint
   (&optional __setpoint)
   (if __setpoint (setq _setpoint __setpoint)) _setpoint)
  (:serialization-length
   ()
   (+
    ;; float64 _kp
    8
    ;; float64 _ki
    8
    ;; float64 _kd
    8
    ;; float64 _feedback
    8
    ;; float64 _setpoint
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _kp
       (sys::poke _kp (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _ki
       (sys::poke _ki (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _kd
       (sys::poke _kd (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _feedback
       (sys::poke _feedback (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _setpoint
       (sys::poke _setpoint (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _kp
     (setq _kp (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _ki
     (setq _ki (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _kd
     (setq _kd (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _feedback
     (setq _feedback (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _setpoint
     (setq _setpoint (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get robot_control::msg4pid :md5sum-) "f4aa24e539f2be8fa5557ca6a4d757bc")
(setf (get robot_control::msg4pid :datatype-) "robot_control/msg4pid")
(setf (get robot_control::msg4pid :definition-)
      "float64 kp
float64 ki
float64 kd
float64 feedback
float64 setpoint
")



(provide :robot_control/msg4pid "f4aa24e539f2be8fa5557ca6a4d757bc")


