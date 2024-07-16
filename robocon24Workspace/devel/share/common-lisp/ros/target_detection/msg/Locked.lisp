; Auto-generated. Do not edit!


(cl:in-package target_detection-msg)


;//! \htmlinclude Locked.msg.html

(cl:defclass <Locked> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (pos
    :reader pos
    :initarg :pos
    :type (cl:vector target_detection-msg:msgLocked)
   :initform (cl:make-array 0 :element-type 'target_detection-msg:msgLocked :initial-element (cl:make-instance 'target_detection-msg:msgLocked))))
)

(cl:defclass Locked (<Locked>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Locked>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Locked)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name target_detection-msg:<Locked> is deprecated: use target_detection-msg:Locked instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Locked>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader target_detection-msg:header-val is deprecated.  Use target_detection-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'pos-val :lambda-list '(m))
(cl:defmethod pos-val ((m <Locked>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader target_detection-msg:pos-val is deprecated.  Use target_detection-msg:pos instead.")
  (pos m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Locked>) ostream)
  "Serializes a message object of type '<Locked>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'pos))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'pos))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Locked>) istream)
  "Deserializes a message object of type '<Locked>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'pos) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'pos)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'target_detection-msg:msgLocked))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Locked>)))
  "Returns string type for a message object of type '<Locked>"
  "target_detection/Locked")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Locked)))
  "Returns string type for a message object of type 'Locked"
  "target_detection/Locked")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Locked>)))
  "Returns md5sum for a message object of type '<Locked>"
  "45a17d35b91831599261552b888c7e20")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Locked)))
  "Returns md5sum for a message object of type 'Locked"
  "45a17d35b91831599261552b888c7e20")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Locked>)))
  "Returns full string definition for message of type '<Locked>"
  (cl:format cl:nil "Header header~%msgLocked[] pos~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: target_detection/msgLocked~%string Class   ~%uint16 centerX~%uint16 centerY ~%float64 centerX_3~%float64 centerY_3~%float64 centerZ_3~%float64 angleX~%float64 angleY~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Locked)))
  "Returns full string definition for message of type 'Locked"
  (cl:format cl:nil "Header header~%msgLocked[] pos~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: target_detection/msgLocked~%string Class   ~%uint16 centerX~%uint16 centerY ~%float64 centerX_3~%float64 centerY_3~%float64 centerZ_3~%float64 angleX~%float64 angleY~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Locked>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'pos) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Locked>))
  "Converts a ROS message object to a list"
  (cl:list 'Locked
    (cl:cons ':header (header msg))
    (cl:cons ':pos (pos msg))
))
