
(cl:in-package :asdf)

(defsystem "target_detection-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Locked" :depends-on ("_package_Locked"))
    (:file "_package_Locked" :depends-on ("_package"))
    (:file "Positions" :depends-on ("_package_Positions"))
    (:file "_package_Positions" :depends-on ("_package"))
    (:file "msgLocked" :depends-on ("_package_msgLocked"))
    (:file "_package_msgLocked" :depends-on ("_package"))
    (:file "position" :depends-on ("_package_position"))
    (:file "_package_position" :depends-on ("_package"))
  ))