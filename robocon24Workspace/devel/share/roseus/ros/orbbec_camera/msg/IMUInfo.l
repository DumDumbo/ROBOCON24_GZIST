;; Auto-generated. Do not edit!


(when (boundp 'orbbec_camera::IMUInfo)
  (if (not (find-package "ORBBEC_CAMERA"))
    (make-package "ORBBEC_CAMERA"))
  (shadow 'IMUInfo (find-package "ORBBEC_CAMERA")))
(unless (find-package "ORBBEC_CAMERA::IMUINFO")
  (make-package "ORBBEC_CAMERA::IMUINFO"))

(in-package "ROS")
;;//! \htmlinclude IMUInfo.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass orbbec_camera::IMUInfo
  :super ros::object
  :slots (_header _noise_density _random_walk _reference_temperature _bias _gravity _scale_misalignment _temperature_slope ))

(defmethod orbbec_camera::IMUInfo
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:noise_density __noise_density) 0.0)
    ((:random_walk __random_walk) 0.0)
    ((:reference_temperature __reference_temperature) 0.0)
    ((:bias __bias) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:gravity __gravity) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:scale_misalignment __scale_misalignment) (make-array 9 :initial-element 0.0 :element-type :float))
    ((:temperature_slope __temperature_slope) (make-array 9 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _noise_density (float __noise_density))
   (setq _random_walk (float __random_walk))
   (setq _reference_temperature (float __reference_temperature))
   (setq _bias __bias)
   (setq _gravity __gravity)
   (setq _scale_misalignment __scale_misalignment)
   (setq _temperature_slope __temperature_slope)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:noise_density
   (&optional __noise_density)
   (if __noise_density (setq _noise_density __noise_density)) _noise_density)
  (:random_walk
   (&optional __random_walk)
   (if __random_walk (setq _random_walk __random_walk)) _random_walk)
  (:reference_temperature
   (&optional __reference_temperature)
   (if __reference_temperature (setq _reference_temperature __reference_temperature)) _reference_temperature)
  (:bias
   (&optional __bias)
   (if __bias (setq _bias __bias)) _bias)
  (:gravity
   (&optional __gravity)
   (if __gravity (setq _gravity __gravity)) _gravity)
  (:scale_misalignment
   (&optional __scale_misalignment)
   (if __scale_misalignment (setq _scale_misalignment __scale_misalignment)) _scale_misalignment)
  (:temperature_slope
   (&optional __temperature_slope)
   (if __temperature_slope (setq _temperature_slope __temperature_slope)) _temperature_slope)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _noise_density
    8
    ;; float64 _random_walk
    8
    ;; float64 _reference_temperature
    8
    ;; float64[3] _bias
    (* 8    3)
    ;; float64[3] _gravity
    (* 8    3)
    ;; float64[9] _scale_misalignment
    (* 8    9)
    ;; float64[9] _temperature_slope
    (* 8    9)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _noise_density
       (sys::poke _noise_density (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _random_walk
       (sys::poke _random_walk (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _reference_temperature
       (sys::poke _reference_temperature (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64[3] _bias
     (dotimes (i 3)
       (sys::poke (elt _bias i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _gravity
     (dotimes (i 3)
       (sys::poke (elt _gravity i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[9] _scale_misalignment
     (dotimes (i 9)
       (sys::poke (elt _scale_misalignment i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[9] _temperature_slope
     (dotimes (i 9)
       (sys::poke (elt _temperature_slope i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _noise_density
     (setq _noise_density (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _random_walk
     (setq _random_walk (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _reference_temperature
     (setq _reference_temperature (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64[3] _bias
   (dotimes (i (length _bias))
     (setf (elt _bias i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _gravity
   (dotimes (i (length _gravity))
     (setf (elt _gravity i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[9] _scale_misalignment
   (dotimes (i (length _scale_misalignment))
     (setf (elt _scale_misalignment i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[9] _temperature_slope
   (dotimes (i (length _temperature_slope))
     (setf (elt _temperature_slope i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;;
   self)
  )

(setf (get orbbec_camera::IMUInfo :md5sum-) "efdf590a2d0b51a471d0de8470a87a58")
(setf (get orbbec_camera::IMUInfo :datatype-) "orbbec_camera/IMUInfo")
(setf (get orbbec_camera::IMUInfo :definition-)
      "std_msgs/Header header
float64 noise_density
float64 random_walk
float64 reference_temperature
float64[3] bias
float64[3] gravity
float64[9] scale_misalignment
float64[9] temperature_slope


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

")



(provide :orbbec_camera/IMUInfo "efdf590a2d0b51a471d0de8470a87a58")


