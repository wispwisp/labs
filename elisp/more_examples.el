;; examples from "Изучаем emacs"

(defun my_style ()
  (interactive)
  (save-excursion
    (search-forward "link")
    (insert " class='some'")))

(global-set-key (kbd "<f9>") 'my_style)

;;major-mode
(defun my-bind-key ()
  (let (my-key-map (current-local-map))
    (local-unset-key (kbd "<f9>"))
    (define-key my-key-map (kbd "<f9>") 'my_style)
    ))
;;(add-hook 'web-mode-hook 'my-bind-key)

(defun my-wrapper ()
  (interactive)
  (let* ((text (buffer-substring (mark) (point)))
	 (lines (split-string text "\n")))
    (kill-region (mark) (point))
    (insert
     (mapconcat '(lambda (s) (concat "<li>" s "</li>"))
		lines "\n"))))

(global-set-key (kbd "<f9>") 'my-wrapper)


