(defun my-capitalize-first-char (str)
  "Capitalize only the first character of the input STRING."
  (when (and str (> (length str) 0))
    (let ((first-char (substring str 0 1))
          (rest-str   (substring str 1)))
      (concat (capitalize first-char) rest-str))))

(defun my-make-class()
  "Create class"
  (interactive)
  (let ((name (concat "C"
		      (my-capitalize-first-char
		       (read-from-minibuffer "Class name: "))))
	(isVirtual (read-from-minibuffer "Is virtual(y/N): ")))

    (insert "\nclass " name
	    "\n{\n"
	    "public:\n"
	    "  " name "();\n"

	    ;; -- Constructors:
	    (if (string= isVirtual "y")
		"  virtual ~"
	      "  ~")
	    name "();\n"

	    ;; -- Rull of five
	    "  " name "(const " name "&) = delete;\n"
	    "  " name "& operator= (const " name "&) = delete;\n"
	    "  " name "(" name "&&) = delete;\n"
	    "  " name "& operator= (" name "&&) = delete;\n"

	    ;; -- private section (If neew THAT order):
	    ;;"private:\n"
	    "};\n"

	    ;; -- Implementation:
	    name "::" name "() {;}\n"
	    name "::~" name "() {;}\n"
	    )
    ))

;;(global-unset-key [f2])
;;(global-set-key [f2] (lambda () (interactive) (my-make-class)))

(global-unset-key "\C-c=")
(global-set-key "\C-c=" 'my-make-class)
