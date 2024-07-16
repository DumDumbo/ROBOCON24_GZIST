;; Auto-generated. Do not edit!


(when (boundp 'target_detection::Positions)
  (if (not (find-package "TARGET_DETECTION"))
    (make-package "TARGET_DETECTION"))
  (shadow 'Positions (find-package "TARGET_DETECTION")))
(unless (find-package "TARGET_DETECTION::POSITIONS")
  (make-package "TARGET_DETECTION::POSITIONS"))

(in-package "ROS")
;;//! \htmlinclude Positions.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass target_detection::Positions
  :super ros::object
  :slots (_header _positions ))

(defmethod target_detection::Positions
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:positions __positions) (let (r) (dotimes (i 0) (push (instance target_detection::position :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _positions __positions)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:positions
   (&rest __positions)
   (if (keywordp (car __positions))
       (send* _positions __positions)
     (progn
       (if __positions (setq _positions (car __positions)))
       _positions)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; target_detection/position[] _positions
    (apply #'+ (send-all _positions :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; target_detection/position[] _positions
     (write-long (length _positions) s)
     (dolist (elem _positions)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; target_detection/position[] _positions
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _positions (let (r) (dotimes (i n) (push (instance target_detection::position :init) r)) r))
     (dolist (elem- _positions)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get target_detection::Positions :md5sum-) "3a4f03400a6799565fe19cfbc22b7c85")
(setf (get target_detection::Positions :datatype-) "target_detection/Positions")
(setf (get target_detection::Positions :definition-)
      "Header header
position[]  positions

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: target_detection/position
string Class   
uint16 centerX
uint16 centerY 
float64 angleX
float64 angleY
float64 distance

")



(provide :target_detection/Positions "3a4f03400a6799565fe19cfbc22b7c85")


