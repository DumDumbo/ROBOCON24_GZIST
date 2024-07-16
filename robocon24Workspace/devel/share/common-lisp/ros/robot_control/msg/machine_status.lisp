; Auto-generated. Do not edit!


(cl:in-package robot_control-msg)


;//! \htmlinclude machine_status.msg.html

(cl:defclass <machine_status> (roslisp-msg-protocol:ros-message)
  ((Roller
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

(cl:defclass machine_status (<machine_status>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <machine_status>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'machine_status)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_control-msg:<machine_status> is deprecated: use robot_control-msg:machine_status instead.")))

(cl:ensure-generic-function 'Roller-val :lambda-list '(m))
(cl:defmethod Roller-val ((m <machine_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-msg:Roller-val is deprecated.  Use robot_control-msg:Roller instead.")
  (Roller m))

(cl:ensure-generic-function 'Mode-val :lambda-list '(m))
(cl:defmethod Mode-val ((m <machine_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-msg:Mode-val is deprecated.  Use robot_control-msg:Mode instead.")
  (Mode m))

(cl:ensure-generic-function 'KeepOrNot-val :lambda-list '(m))
(cl:defmethod KeepOrNot-val ((m <machine_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-msg:KeepOrNot-val is deprecated.  Use robot_control-msg:KeepOrNot instead.")
  (KeepOrNot m))

(cl:ensure-generic-function 'PlaceOrNot-val :lambda-list '(m))
(cl:defmethod PlaceOrNot-val ((m <machine_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-msg:PlaceOrNot-val is deprecated.  Use robot_control-msg:PlaceOrNot instead.")
  (PlaceOrNot m))

(cl:ensure-generic-function 'RobotStatus-val :lambda-list '(m))
(cl:defmethod RobotStatus-val ((m <machine_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-msg:RobotStatus-val is deprecated.  Use robot_control-msg:RobotStatus instead.")
  (RobotStatus m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <machine_status>) ostream)
  "Serializes a message object of type '<machine_status>"
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <machine_status>) istream)
  "Deserializes a message object of type '<machine_status>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<machine_status>)))
  "Returns string type for a message object of type '<machine_status>"
  "robot_control/machine_status")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'machine_status)))
  "Returns string type for a message object of type 'machine_status"
  "robot_control/machine_status")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<machine_status>)))
  "Returns md5sum for a message object of type '<machine_status>"
  "358fea0a2efe9c679e20648d6430914a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'machine_status)))
  "Returns md5sum for a message object of type 'machine_status"
  "358fea0a2efe9c679e20648d6430914a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<machine_status>)))
  "Returns full string definition for message of type '<machine_status>"
  (cl:format cl:nil "uint8 Roller~%uint8 Mode~%uint8 KeepOrNot~%uint8 PlaceOrNot~%string RobotStatus~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'machine_status)))
  "Returns full string definition for message of type 'machine_status"
  (cl:format cl:nil "uint8 Roller~%uint8 Mode~%uint8 KeepOrNot~%uint8 PlaceOrNot~%string RobotStatus~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <machine_status>))
  (cl:+ 0
     1
     1
     1
     1
     4 (cl:length (cl:slot-value msg 'RobotStatus))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <machine_status>))
  "Converts a ROS message object to a list"
  (cl:list 'machine_status
    (cl:cons ':Roller (Roller msg))
    (cl:cons ':Mode (Mode msg))
    (cl:cons ':KeepOrNot (KeepOrNot msg))
    (cl:cons ':PlaceOrNot (PlaceOrNot msg))
    (cl:cons ':RobotStatus (RobotStatus msg))
))
