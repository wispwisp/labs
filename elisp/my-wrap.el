(defun my-def-to-int ()
  (interactive)
  (kill-region (line-beginning-position) (line-end-position))
  (insert "#define ")
  (yank)
  (insert " int"))

(global-unset-key (kbd "<f12>"))
(global-set-key (kbd "<f12>") 'my-def-to-int)
