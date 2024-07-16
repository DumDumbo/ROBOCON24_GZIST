; Auto-generated. Do not edit!


(cl:in-package target_detection-msg)


;//! \htmlinclude msgLocked.msg.html

(cl:defclass <msgLocked> (roslisp-msg-protocol:ros-message)
  ((Class
    :reader Class
    :initarg :Class
    :type cl:string
    :initform "")
   (centerX
    :reader centerX
    :initarg :centerX
    :type cl:fixnum
    :initform 0)
   (centerY
    :reader centerY
    :initarg :centerY
    :type cl:fixnum
    :initform 0)
   (centerX_3
    :reader centerX_3
    :initarg :centerX_3
    :type cl:float
    :initform 0.0)
   (centerY_3
    :reader centerY_3
    :initarg :centerY_3
    :type cl:float
    :initform 0.0)
   (centerZ_3
    :reader centerZ_3
    :initarg :centerZ_3
    :type cl:float
    :initform 0.0)
   (angleX
    :reader angleX
    :initarg :angleX
    :type cl:float
    :initform 0.0)
   (angleY
    :reader angleY
    :initarg :angleY
    :type cl:float
    :initform 0.0))
)

(cl:defclass msgLocked (<msgLocked>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msgLocked>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msgLocked)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name target_detection-msg:<msgLocked> is deprecated: use target_detection-msg:msgLocked instead.")))

(cl:ensure-generic-function 'Class-val :lambda-list '(m))
(cl:defmethod Class-val ((m <msgLocked>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader target_detection-msg:Class-val is deprecated.  Use target_detection-msg:Class instead.")
  (Class m))

(cl:ensure-generic-function 'centerX-val :lambda-list '(m))
(cl:defmethod centerX-val ((m <msgLocked>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader target_detection-msg:centerX-val is deprecated.  Use target_detection-msg:centerX instead.")
  (centerX m))

(cl:ensure-generic-function 'centerY-val :lambda-list '(m))
(cl:defmethod centerY-val ((m <msgLocked>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader target_detection-msg:centerY-val is deprecated.  Use target_detection-msg:centerY instead.")
  (centerY m))

(cl:ensure-generic-function 'centerX_3-val :lambda-list '(m))
(cl:defmethod centerX_3-val ((m <msgLocked>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader target_detection-msg:centerX_3-val is deprecated.  Use target_detection-msg:centerX_3 instead.")
  (centerX_3 m))

(cl:ensure-generic-function 'centerY_3-val :lambda-list '(m))
(cl:defmethod centerY_3-val ((m <msgLocked>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader target_detection-msg:centerY_3-val is deprecated.  Use target_detection-msg:centerY_3 instead.")
  (centerY_3 m))

(cl:ensure-generic-function 'centerZ_3-val :lambda-list '(m))
(cl:defmethod centerZ_3-val ((m <msgLocked>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader target_detection-msg:centerZ_3-val is deprecated.  Use target_detection-msg:centerZ_3 instead.")
  (centerZ_3 m))

(cl:ensure-generic-function 'angleX-val :lambda-list '(m))
(cl:defmethod angleX-val ((m <msgLocked>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader target_detection-msg:angleX-val is deprecated.  Use target_detection-msg:angleX instead.")
  (angleX m))

(cl:ensure-generic-function 'angleY-val :lambda-list '(m))
(cl:defmethod angleY-val ((m <msgLocked>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader target_detection-msg:angleY-val is deprecated.  Use target_detection-msg:angleY instead.")
  (angleY m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msgLocked>) ostream)
  "Serializes a message object of type '<msgLocked>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'Class))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'Class))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'centerX)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'centerX)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'centerY)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'centerY)) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'centerX_3))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'centerY_3))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'centerZ_3))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'angleX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'angleY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msgLocked>) istream)
  "Deserializes a message object of type '<msgLocked>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Class) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'Class) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'centerX)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'centerX)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'centerY)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'centerY)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'centerX_3) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'centerY_3) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'centerZ_3) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angleX) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angleY) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msgLocked>)))
  "Returns string type for a message object of type '<msgLocked>"
  "target_detection/msgLocked")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msgLocked)))
  "Returns string type for a message object of type 'msgLocked"
  "target_detection/msgLocked")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msgLocked>)))
  "Returns md5sum for a message object of type '<msgLocked>"
  "d45d2d0fb3ceb83242a976ffd12f2dfc")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msgLocked)))
  "Returns md5sum for a message object of type 'msgLocked"
  "d45d2d0fb3ceb83242a976ffd12f2dfc")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msgLocked>)))
  "Returns full string definition for message of type '<msgLocked>"
  (cl:format cl:nil "string Class   ~%uint16 centerX~%uint16 centerY ~%float64 centerX_3~%float64 centerY_3~%float64 centerZ_3~%float64 angleX~%float64 angleY~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msgLocked)))
  "Returns full string definition for message of type 'msgLocked"
  (cl:format cl:nil "string Class   ~%uint16 centerX~%uint16 centerY ~%float64 centerX_3~%float64 centerY_3~%float64 centerZ_3~%float64 angleX~%float64 angleY~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msgLocked>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'Class))
     2
     2
     8
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msgLocked>))
  "Converts a ROS message object to a list"
  (cl:list 'msgLocked
    (cl:cons ':Class (Class msg))
    (cl:cons ':centerX (centerX msg))
    (cl:cons ':centerY (centerY msg))
    (cl:cons ':centerX_3 (centerX_3 msg))
    (cl:cons ':centerY_3 (centerY_3 msg))
    (cl:cons ':centerZ_3 (centerZ_3 msg))
    (cl:cons ':angleX (angleX msg))
    (cl:cons ':angleY (angleY msg))
))
