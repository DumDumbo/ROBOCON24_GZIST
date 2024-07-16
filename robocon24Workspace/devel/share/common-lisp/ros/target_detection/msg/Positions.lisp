; Auto-generated. Do not edit!


(cl:in-package target_detection-msg)


;//! \htmlinclude Positions.msg.html

(cl:defclass <Positions> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (positions
    :reader positions
    :initarg :positions
    :type (cl:vector target_detection-msg:position)
   :initform (cl:make-array 0 :element-type 'target_detection-msg:position :initial-element (cl:make-instance 'target_detection-msg:position))))
)

(cl:defclass Positions (<Positions>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Positions>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Positions)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name target_detection-msg:<Positions> is deprecated: use target_detection-msg:Positions instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Positions>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader target_detection-msg:header-val is deprecated.  Use target_detection-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'positions-val :lambda-list '(m))
(cl:defmethod positions-val ((m <Positions>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader target_detection-msg:positions-val is deprecated.  Use target_detection-msg:positions instead.")
  (positions m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Positions>) ostream)
  "Serializes a message object of type '<Positions>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'positions))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'positions))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Positions>) istream)
  "Deserializes a message object of type '<Positions>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'positions) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'positions)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'target_detection-msg:position))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Positions>)))
  "Returns string type for a message object of type '<Positions>"
  "target_detection/Positions")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Positions)))
  "Returns string type for a message object of type 'Positions"
  "target_detection/Positions")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Positions>)))
  "Returns md5sum for a message object of type '<Positions>"
  "3a4f03400a6799565fe19cfbc22b7c85")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Positions)))
  "Returns md5sum for a message object of type 'Positions"
  "3a4f03400a6799565fe19cfbc22b7c85")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Positions>)))
  "Returns full string definition for message of type '<Positions>"
  (cl:format cl:nil "Header header~%position[]  positions~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: target_detection/position~%string Class   ~%uint16 centerX~%uint16 centerY ~%float64 angleX~%float64 angleY~%float64 distance~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Positions)))
  "Returns full string definition for message of type 'Positions"
  (cl:format cl:nil "Header header~%position[]  positions~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: target_detection/position~%string Class   ~%uint16 centerX~%uint16 centerY ~%float64 angleX~%float64 angleY~%float64 distance~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Positions>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'positions) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Positions>))
  "Converts a ROS message object to a list"
  (cl:list 'Positions
    (cl:cons ':header (header msg))
    (cl:cons ':positions (positions msg))
))
