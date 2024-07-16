;; Auto-generated. Do not edit!


(when (boundp 'astra_camera::GetDouble)
  (if (not (find-package "ASTRA_CAMERA"))
    (make-package "ASTRA_CAMERA"))
  (shadow 'GetDouble (find-package "ASTRA_CAMERA")))
(unless (find-package "ASTRA_CAMERA::GETDOUBLE")
  (make-package "ASTRA_CAMERA::GETDOUBLE"))
(unless (find-package "ASTRA_CAMERA::GETDOUBLEREQUEST")
  (make-package "ASTRA_CAMERA::GETDOUBLEREQUEST"))
(unless (find-package "ASTRA_CAMERA::GETDOUBLERESPONSE")
  (make-package "ASTRA_CAMERA::GETDOUBLERESPONSE"))

(in-package "ROS")





(defclass astra_camera::GetDoubleRequest
  :super ros::object
  :slots ())

(defmethod astra_camera::GetDoubleRequest
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass astra_camera::GetDoubleResponse
  :super ros::object
  :slots (_data _success _message ))

(defmethod astra_camera::GetDoubleResponse
  (:init
   (&key
    ((:data __data) 0.0)
    ((:success __success) nil)
    ((:message __message) "")
    )
   (send-super :init)
   (setq _data (float __data))
   (setq _success __success)
   (setq _message (string __message))
   self)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:message
   (&optional __message)
   (if __message (setq _message __message)) _message)
  (:serialization-length
   ()
   (+
    ;; float64 _data
    8
    ;; bool _success
    1
    ;; string _message
    4 (length _message)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _data
       (sys::poke _data (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;; string _message
       (write-long (length _message) s) (princ _message s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _data
     (setq _data (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; string _message
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _message (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass astra_camera::GetDouble
  :super ros::object
  :slots ())

(setf (get astra_camera::GetDouble :md5sum-) "edb830bb55b38159c2bb5a997bcb994d")
(setf (get astra_camera::GetDouble :datatype-) "astra_camera/GetDouble")
(setf (get astra_camera::GetDouble :request) astra_camera::GetDoubleRequest)
(setf (get astra_camera::GetDouble :response) astra_camera::GetDoubleResponse)

(defmethod astra_camera::GetDoubleRequest
  (:response () (instance astra_camera::GetDoubleResponse :init)))

(setf (get astra_camera::GetDoubleRequest :md5sum-) "edb830bb55b38159c2bb5a997bcb994d")
(setf (get astra_camera::GetDoubleRequest :datatype-) "astra_camera/GetDoubleRequest")
(setf (get astra_camera::GetDoubleRequest :definition-)
      "---
float64 data
bool success
string message

")

(setf (get astra_camera::GetDoubleResponse :md5sum-) "edb830bb55b38159c2bb5a997bcb994d")
(setf (get astra_camera::GetDoubleResponse :datatype-) "astra_camera/GetDoubleResponse")
(setf (get astra_camera::GetDoubleResponse :definition-)
      "---
float64 data
bool success
string message

")



(provide :astra_camera/GetDouble "edb830bb55b38159c2bb5a997bcb994d")


