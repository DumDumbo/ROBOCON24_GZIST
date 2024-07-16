; Auto-generated. Do not edit!


(cl:in-package astra_camera-srv)


;//! \htmlinclude GetDouble-request.msg.html

(cl:defclass <GetDouble-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetDouble-request (<GetDouble-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetDouble-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetDouble-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name astra_camera-srv:<GetDouble-request> is deprecated: use astra_camera-srv:GetDouble-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetDouble-request>) ostream)
  "Serializes a message object of type '<GetDouble-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetDouble-request>) istream)
  "Deserializes a message object of type '<GetDouble-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetDouble-request>)))
  "Returns string type for a service object of type '<GetDouble-request>"
  "astra_camera/GetDoubleRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetDouble-request)))
  "Returns string type for a service object of type 'GetDouble-request"
  "astra_camera/GetDoubleRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetDouble-request>)))
  "Returns md5sum for a message object of type '<GetDouble-request>"
  "edb830bb55b38159c2bb5a997bcb994d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetDouble-request)))
  "Returns md5sum for a message object of type 'GetDouble-request"
  "edb830bb55b38159c2bb5a997bcb994d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetDouble-request>)))
  "Returns full string definition for message of type '<GetDouble-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetDouble-request)))
  "Returns full string definition for message of type 'GetDouble-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetDouble-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetDouble-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetDouble-request
))
;//! \htmlinclude GetDouble-response.msg.html

(cl:defclass <GetDouble-response> (roslisp-msg-protocol:ros-message)
  ((data
    :reader data
    :initarg :data
    :type cl:float
    :initform 0.0)
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil)
   (message
    :reader message
    :initarg :message
    :type cl:string
    :initform ""))
)

(cl:defclass GetDouble-response (<GetDouble-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetDouble-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetDouble-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name astra_camera-srv:<GetDouble-response> is deprecated: use astra_camera-srv:GetDouble-response instead.")))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <GetDouble-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astra_camera-srv:data-val is deprecated.  Use astra_camera-srv:data instead.")
  (data m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <GetDouble-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astra_camera-srv:success-val is deprecated.  Use astra_camera-srv:success instead.")
  (success m))

(cl:ensure-generic-function 'message-val :lambda-list '(m))
(cl:defmethod message-val ((m <GetDouble-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astra_camera-srv:message-val is deprecated.  Use astra_camera-srv:message instead.")
  (message m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetDouble-response>) ostream)
  "Serializes a message object of type '<GetDouble-response>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'message))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'message))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetDouble-response>) istream)
  "Deserializes a message object of type '<GetDouble-response>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'data) (roslisp-utils:decode-double-float-bits bits)))
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'message) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'message) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetDouble-response>)))
  "Returns string type for a service object of type '<GetDouble-response>"
  "astra_camera/GetDoubleResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetDouble-response)))
  "Returns string type for a service object of type 'GetDouble-response"
  "astra_camera/GetDoubleResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetDouble-response>)))
  "Returns md5sum for a message object of type '<GetDouble-response>"
  "edb830bb55b38159c2bb5a997bcb994d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetDouble-response)))
  "Returns md5sum for a message object of type 'GetDouble-response"
  "edb830bb55b38159c2bb5a997bcb994d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetDouble-response>)))
  "Returns full string definition for message of type '<GetDouble-response>"
  (cl:format cl:nil "float64 data~%bool success~%string message~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetDouble-response)))
  "Returns full string definition for message of type 'GetDouble-response"
  (cl:format cl:nil "float64 data~%bool success~%string message~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetDouble-response>))
  (cl:+ 0
     8
     1
     4 (cl:length (cl:slot-value msg 'message))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetDouble-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetDouble-response
    (cl:cons ':data (data msg))
    (cl:cons ':success (success msg))
    (cl:cons ':message (message msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetDouble)))
  'GetDouble-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetDouble)))
  'GetDouble-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetDouble)))
  "Returns string type for a service object of type '<GetDouble>"
  "astra_camera/GetDouble")