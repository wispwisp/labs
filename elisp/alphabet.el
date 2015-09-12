(defun my_alphabet()
  (let ((start-range 1072)
	(end-range 1103))
    (defun ins (number)
      (insert " " (string number)))
    (insert "\nalphabet[" 
	    (number-to-string start-range)
	    "-"
	    (number-to-string end-range)
	    "]:")
    (mapcar 'ins (number-sequence start-range end-range))))

(my_alphabet)
