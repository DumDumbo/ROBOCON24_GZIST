;; Auto-generated. Do not edit!


(when (boundp 'target_detection::msgLocked)
  (if (not (find-package "TARGET_DETECTION"))
    (make-package "TARGET_DETECTION"))
  (shadow 'msgLocked (find-package "TARGET_DETECTION")))
(unless (find-package "TARGET_DETECTION::MSGLOCKED")
  (make-package "TARGET_DETECTION::MSGLOCKED"))

(in-package "ROS")
;;//! \htmlinclude msgLocked.msg.html


(defclass target_detection::msgLocked
  :super ros::object
  :slots (_Class _centerX _centerY _centerX_3 _centerY_3 _centerZ_3 _angleX _angleY ))

(defmethod target_detection::msgLocked
  (:init
   (&key
    ((:Class __Class) "")
    ((:centerX __centerX) 0)
    ((:centerY __centerY) 0)
    ((:centerX_3 __centerX_3) 0.0)
    ((:centerY_3 __centerY_3) 0.0)
    ((:centerZ_3 __centerZ_3) 0.0)
    ((:angleX __angleX) 0.0)
    ((:angleY __angleY) 0.0)
    )
   (send-super :init)
   (setq _Class (string __Class))
   (setq _centerX (round __centerX))
   (setq _centerY (round __centerY))
   (setq _centerX_3 (float __centerX_3))
   (setq _centerY_3 (float __centerY_3))
   (setq _centerZ_3 (float __centerZ_3))
   (setq _angleX (float __angleX))
   (setq _angleY (float __angleY))
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
  (:centerX_3
   (&optional __centerX_3)
   (if __centerX_3 (setq _centerX_3 __centerX_3)) _centerX_3)
  (:centerY_3
   (&optional __centerY_3)
   (if __centerY_3 (setq _centerY_3 __centerY_3)) _centerY_3)
  (:centerZ_3
   (&optional __centerZ_3)
   (if __centerZ_3 (setq _centerZ_3 __centerZ_3)) _centerZ_3)
  (:angleX
   (&optional __angleX)
   (if __angleX (setq _angleX __angleX)) _angleX)
  (:angleY
   (&optional __angleY)
   (if __angleY (setq _angleY __angleY)) _angleY)
  (:serialization-length
   ()
   (+
    ;; string _Class
    4 (length _Class)
    ;; uint16 _centerX
    2
    ;; uint16 _centerY
    2
    ;; float64 _centerX_3
    8
    ;; float64 _centerY_3
    8
    ;; float64 _centerZ_3
    8
    ;; float64 _angleX
    8
    ;; float64 _angleY
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
     ;; float64 _centerX_3
       (sys::poke _centerX_3 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _centerY_3
       (sys::poke _centerY_3 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _centerZ_3
       (sys::poke _centerZ_3 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _angleX
       (sys::poke _angleX (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _angleY
       (sys::poke _angleY (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
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
   ;; float64 _centerX_3
     (setq _centerX_3 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _centerY_3
     (setq _centerY_3 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _centerZ_3
     (setq _centerZ_3 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _angleX
     (setq _angleX (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _angleY
     (setq _angleY (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get target_detection::msgLocked :md5sum-) "d45d2d0fb3ceb83242a976ffd12f2dfc")
(setf (get target_detection::msgLocked :datatype-) "target_detection/msgLocked")
(setf (get target_detection::msgLocked :definition-)
      "string Class   
uint16 centerX
uint16 centerY 
float64 centerX_3
float64 centerY_3
float64 centerZ_3
float64 angleX
float64 angleY

")



(provide :target_detection/msgLocked "d45d2d0fb3ceb83242a976ffd12f2dfc")


