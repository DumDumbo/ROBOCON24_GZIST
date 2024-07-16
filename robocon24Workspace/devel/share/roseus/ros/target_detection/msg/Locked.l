;; Auto-generated. Do not edit!


(when (boundp 'target_detection::Locked)
  (if (not (find-package "TARGET_DETECTION"))
    (make-package "TARGET_DETECTION"))
  (shadow 'Locked (find-package "TARGET_DETECTION")))
(unless (find-package "TARGET_DETECTION::LOCKED")
  (make-package "TARGET_DETECTION::LOCKED"))

(in-package "ROS")
;;//! \htmlinclude Locked.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass target_detection::Locked
  :super ros::object
  :slots (_header _pos ))

(defmethod target_detection::Locked
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:pos __pos) (let (r) (dotimes (i 0) (push (instance target_detection::msgLocked :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _pos __pos)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:pos
   (&rest __pos)
   (if (keywordp (car __pos))
       (send* _pos __pos)
     (progn
       (if __pos (setq _pos (car __pos)))
       _pos)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; target_detection/msgLocked[] _pos
    (apply #'+ (send-all _pos :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; target_detection/msgLocked[] _pos
     (write-long (length _pos) s)
     (dolist (elem _pos)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; target_detection/msgLocked[] _pos
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _pos (let (r) (dotimes (i n) (push (instance target_detection::msgLocked :init) r)) r))
     (dolist (elem- _pos)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get target_detection::Locked :md5sum-) "45a17d35b91831599261552b888c7e20")
(setf (get target_detection::Locked :datatype-) "target_detection/Locked")
(setf (get target_detection::Locked :definition-)
      "Header header
msgLocked[] pos

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
MSG: target_detection/msgLocked
string Class   
uint16 centerX
uint16 centerY 
float64 centerX_3
float64 centerY_3
float64 centerZ_3
float64 angleX
float64 angleY

")



(provide :target_detection/Locked "45a17d35b91831599261552b888c7e20")


