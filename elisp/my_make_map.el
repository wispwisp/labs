(defun my-wrap (text)
  (let* ((l (split-string text " "))
         (f (car l))
         (s (car (cdr l))))
    (concat "{\"" f "\", \"" s "\"}")))

(defun my-wrapper ()
  (interactive)
  (let* ((text (buffer-substring (mark) (point)))
         (lines (split-string text "\n")))
    (kill-region (mark) (point))
    (insert
     (mapconcat '(lambda (s) (my-wrap s)) lines "\n"))))

;; Usage:

;; А D090
;; Б D091
;; В D092
;; Г D093
;; Д D094

;; =>

;; {"А", "D090"}
;; {"Б", "D091"}
;; {"В", "D092"}
;; {"Г", "D093"}
;; {"Д", "D094"}
