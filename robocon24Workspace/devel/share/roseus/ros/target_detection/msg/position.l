;; Auto-generated. Do not edit!


(when (boundp 'target_detection::position)
  (if (not (find-package "TARGET_DETECTION"))
    (make-package "TARGET_DETECTION"))
  (shadow 'position (find-package "TARGET_DETECTION")))
(unless (find-package "TARGET_DETECTION::POSITION")
  (make-package "TARGET_DETECTION::POSITION"))

(in-package "ROS")
;;//! \htmlinclude position.msg.html


(defclass target_detection::position
  :super ros::object
  :slots (_Class _centerX _centerY _angleX _angleY _distance ))

(defmethod target_detection::position
  (:init
   (&key
    ((:Class __Class) "")
    ((:centerX __centerX) 0)
    ((:centerY __centerY) 0)
    ((:angleX __angleX) 0.0)
    ((:angleY __angleY) 0.0)
    ((:distance __distance) 0.0)
    )
   (send-super :init)
   (setq _Class (string __Class))
   (setq _centerX (round __centerX))
   (setq _centerY (round __centerY))
   (setq _angleX (float __angleX))
   (setq _angleY (float __angleY))
   (setq _distance (float __distance))
   self)
  (:Class
   (&optional __Class)
   (if __Class (setq _Class __Class)) _Class)
  (:centerX
   (&optional __centerX)
   (if __centerX (setq _centerX __centerX)) _centerX)
  (:centerY
   (&optional __centerY)
   (if __centerY (setq _centerY __centerY)) _centerY)
  (:angleX
   (&optional __angleX)
   (if __angleX (setq _angleX __angleX)) _angleX)
  (:angleY
   (&optional __angleY)
   (if __angleY (setq _angleY __angleY)) _angleY)
  (:distance
   (&optional __distance)
   (if __distance (setq _distance __distance)) _distance)
  (:serialization-length
   ()
   (+
    ;; string _Class
    4 (length _Class)
    ;; uint16 _centerX
    2
    ;; uint16 _centerY
    2
    ;; float64 _angleX
    8
    ;; float64 _angleY
    8
    ;; float64 _distance
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _Class
       (write-long (length _Class) s) (princ _Class s)
     ;; uint16 _centerX
       (write-word _centerX s)
     ;; uint16 _centerY
       (write-word _centerY s)
     ;; float64 _angleX
       (sys::poke _angleX (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _angleY
       (sys::poke _angleY (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _distance
       (sys::poke _distance (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _Class
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _Class (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; uint16 _centerX
     (setq _centerX (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _centerY
     (setq _centerY (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; float64 _angleX
     (setq _angleX (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _angleY
     (setq _angleY (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _distance
     (setq _distance (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get target_detection::position :md5sum-) "6b33d03305c0dd807b7a4b6591831277")
(setf (get target_detection::position :datatype-) "target_detection/position")
(setf (get target_detection::position :definition-)
      "string Class   
uint16 centerX
uint16 centerY 
float64 angleX
float64 angleY
float64 distance

")



(provide :target_detection/position "6b33d03305c0dd807b7a4b6591831277")


