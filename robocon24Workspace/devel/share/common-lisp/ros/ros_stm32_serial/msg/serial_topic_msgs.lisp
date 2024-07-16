; Auto-generated. Do not edit!


(cl:in-package ros_stm32_serial-msg)


;//! \htmlinclude serial_topic_msgs.msg.html

(cl:defclass <serial_topic_msgs> (roslisp-msg-protocol:ros-message)
  ((flag
    :reader flag
    :initarg :flag
    :type cl:float
    :initform 0.0)
   (status
    :reader status
    :initarg :status
    :type cl:float
    :initform 0.0)
   (linearX
    :reader linearX
    :initarg :linearX
    :type cl:float
    :initform 0.0)
   (linearY
    :reader linearY
    :initarg :linearY
    :type cl:float
    :initform 0.0)
   (angularZ
    :reader angularZ
    :initarg :angularZ
    :type cl:float
    :initform 0.0)
   (LaserFront
    :reader LaserFront
    :initarg :LaserFront
    :type cl:integer
    :initform 0)
   (LaserL
    :reader LaserL
    :initarg :LaserL
    :type cl:integer
    :initform 0)
   (LaserR
    :reader LaserR
    :initarg :LaserR
    :type cl:integer
    :initform 0)
   (LaserRear
    :reader LaserRear
    :initarg :LaserRear
    :type cl:integer
    :initform 0)
   (Roller
    :reader Roller
    :initarg :Roller
    :type cl:fixnum
    :initform 0)
   (Mode
    :reader Mode
    :initarg :Mode
    :type cl:fixnum
    :initform 0)
   (KeepOrNot
    :reader KeepOrNot
    :initarg :KeepOrNot
    :type cl:fixnum
    :initform 0)
   (PlaceOrNot
    :reader PlaceOrNot
    :initarg :PlaceOrNot
    :type cl:fixnum
    :initform 0)
   (RobotStatus
    :reader RobotStatus
    :initarg :RobotStatus
    :type cl:string
    :initform ""))
)

(cl:defclass serial_topic_msgs (<serial_topic_msgs>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <serial_topic_msgs>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'serial_topic_msgs)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_stm32_serial-msg:<serial_topic_msgs> is deprecated: use ros_stm32_serial-msg:serial_topic_msgs instead.")))

(cl:ensure-generic-function 'flag-val :lambda-list '(m))
(cl:defmethod flag-val ((m <serial_topic_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_stm32_serial-msg:flag-val is deprecated.  Use ros_stm32_serial-msg:flag instead.")
  (flag m))

(cl:ensure-generic-function 'status-val :lambda-list '(m))
(cl:defmethod status-val ((m <serial_topic_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_stm32_serial-msg:status-val is deprecated.  Use ros_stm32_serial-msg:status instead.")
  (status m))

(cl:ensure-generic-function 'linearX-val :lambda-list '(m))
(cl:defmethod linearX-val ((m <serial_topic_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_stm32_serial-msg:linearX-val is deprecated.  Use ros_stm32_serial-msg:linearX instead.")
  (linearX m))

(cl:ensure-generic-function 'linearY-val :lambda-list '(m))
(cl:defmethod linearY-val ((m <serial_topic_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_stm32_serial-msg:linearY-val is deprecated.  Use ros_stm32_serial-msg:linearY instead.")
  (linearY m))

(cl:ensure-generic-function 'angularZ-val :lambda-list '(m))
(cl:defmethod angularZ-val ((m <serial_topic_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_stm32_serial-msg:angularZ-val is deprecated.  Use ros_stm32_serial-msg:angularZ instead.")
  (angularZ m))

(cl:ensure-generic-function 'LaserFront-val :lambda-list '(m))
(cl:defmethod LaserFront-val ((m <serial_topic_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_stm32_serial-msg:LaserFront-val is deprecated.  Use ros_stm32_serial-msg:LaserFront instead.")
  (LaserFront m))

(cl:ensure-generic-function 'LaserL-val :lambda-list '(m))
(cl:defmethod LaserL-val ((m <serial_topic_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_stm32_serial-msg:LaserL-val is deprecated.  Use ros_stm32_serial-msg:LaserL instead.")
  (LaserL m))

(cl:ensure-generic-function 'LaserR-val :lambda-list '(m))
(cl:defmethod LaserR-val ((m <serial_topic_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_stm32_serial-msg:LaserR-val is deprecated.  Use ros_stm32_serial-msg:LaserR instead.")
  (LaserR m))

(cl:ensure-generic-function 'LaserRear-val :lambda-list '(m))
(cl:defmethod LaserRear-val ((m <serial_topic_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_stm32_serial-msg:LaserRear-val is deprecated.  Use ros_stm32_serial-msg:LaserRear instead.")
  (LaserRear m))

(cl:ensure-generic-function 'Roller-val :lambda-list '(m))
(cl:defmethod Roller-val ((m <serial_topic_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_stm32_serial-msg:Roller-val is deprecated.  Use ros_stm32_serial-msg:Roller instead.")
  (Roller m))

(cl:ensure-generic-function 'Mode-val :lambda-list '(m))
(cl:defmethod Mode-val ((m <serial_topic_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_stm32_serial-msg:Mode-val is deprecated.  Use ros_stm32_serial-msg:Mode instead.")
  (Mode m))

(cl:ensure-generic-function 'KeepOrNot-val :lambda-list '(m))
(cl:defmethod KeepOrNot-val ((m <serial_topic_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_stm32_serial-msg:KeepOrNot-val is deprecated.  Use ros_stm32_serial-msg:KeepOrNot instead.")
  (KeepOrNot m))

(cl:ensure-generic-function 'PlaceOrNot-val :lambda-list '(m))
(cl:defmethod PlaceOrNot-val ((m <serial_topic_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_stm32_serial-msg:PlaceOrNot-val is deprecated.  Use ros_stm32_serial-msg:PlaceOrNot instead.")
  (PlaceOrNot m))

(cl:ensure-generic-function 'RobotStatus-val :lambda-list '(m))
(cl:defmethod RobotStatus-val ((m <serial_topic_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_stm32_serial-msg:RobotStatus-val is deprecated.  Use ros_stm32_serial-msg:RobotStatus instead.")
  (RobotStatus m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <serial_topic_msgs>) ostream)
  "Serializes a message object of type '<serial_topic_msgs>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'flag))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'status))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'linearX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'linearY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'angularZ))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'LaserFront)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'LaserL)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'LaserR)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'LaserRear)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Roller)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Mode)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'KeepOrNot)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'PlaceOrNot)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'RobotStatus))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'RobotStatus))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <serial_topic_msgs>) istream)
  "Deserializes a message object of type '<serial_topic_msgs>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'flag) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'status) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'linearX) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'linearY) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angularZ) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'LaserFront) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'LaserL) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'LaserR) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'LaserRear) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Roller)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Mode)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'KeepOrNot)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'PlaceOrNot)) (cl:read-byte istream))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'RobotStatus) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'RobotStatus) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<serial_topic_msgs>)))
  "Returns string type for a message object of type '<serial_topic_msgs>"
  "ros_stm32_serial/serial_topic_msgs")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'serial_topic_msgs)))
  "Returns string type for a message object of type 'serial_topic_msgs"
  "ros_stm32_serial/serial_topic_msgs")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<serial_topic_msgs>)))
  "Returns md5sum for a message object of type '<serial_topic_msgs>"
  "d5bec99ac5726ba6e665cc5e4980b15b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'serial_topic_msgs)))
  "Returns md5sum for a message object of type 'serial_topic_msgs"
  "d5bec99ac5726ba6e665cc5e4980b15b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<serial_topic_msgs>)))
  "Returns full string definition for message of type '<serial_topic_msgs>"
  (cl:format cl:nil "float64 flag~%float64 status~%float64 linearX~%float64 linearY~%float64 angularZ~%int32 LaserFront~%int32 LaserL~%int32 LaserR~%int32 LaserRear~%uint8 Roller~%uint8 Mode~%uint8 KeepOrNot~%uint8 PlaceOrNot~%string RobotStatus~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'serial_topic_msgs)))
  "Returns full string definition for message of type 'serial_topic_msgs"
  (cl:format cl:nil "float64 flag~%float64 status~%float64 linearX~%float64 linearY~%float64 angularZ~%int32 LaserFront~%int32 LaserL~%int32 LaserR~%int32 LaserRear~%uint8 Roller~%uint8 Mode~%uint8 KeepOrNot~%uint8 PlaceOrNot~%string RobotStatus~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <serial_topic_msgs>))
  (cl:+ 0
     8
     8
     8
     8
     8
     4
     4
     4
     4
     1
     1
     1
     1
     4 (cl:length (cl:slot-value msg 'RobotStatus))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <serial_topic_msgs>))
  "Converts a ROS message object to a list"
  (cl:list 'serial_topic_msgs
    (cl:cons ':flag (flag msg))
    (cl:cons ':status (status msg))
    (cl:cons ':linearX (linearX msg))
    (cl:cons ':linearY (linearY msg))
    (cl:cons ':angularZ (angularZ msg))
    (cl:cons ':LaserFront (LaserFront msg))
    (cl:cons ':LaserL (LaserL msg))
    (cl:cons ':LaserR (LaserR msg))
    (cl:cons ':LaserRear (LaserRear msg))
    (cl:cons ':Roller (Roller msg))
    (cl:cons ':Mode (Mode msg))
    (cl:cons ':KeepOrNot (KeepOrNot msg))
    (cl:cons ':PlaceOrNot (PlaceOrNot msg))
    (cl:cons ':RobotStatus (RobotStatus msg))
))
