(defun my-grep()
  "Fast grep call with '-Rni' flags and quoted text"
  (interactive)
  (let* ((pattern (read-from-minibuffer "Search pattern: "))
         (path (read-from-minibuffer "Path: "))
         (command (format "grep -Rni \"%s\" %s" pattern path)))
    ;;(insert command)
    ;;(shell-command command)
    (async-shell-command command)
    ))

(global-unset-key (kbd "<f6>"))
(global-set-key (kbd "<f6>") 'my-grep)

(defun my-grep-marked()
  "Fast grep call with '-Rni' flags and quoted text"
  (interactive)
  (let* ((pattern (buffer-substring (mark) (point)))
         (path (read-from-minibuffer "Path: "))
         (command (format "grep -Rni \"%s\" %s" pattern path)))
    ;;(insert command)
    ;;(shell-command command)
    (async-shell-command command)
    ))

(global-unset-key (kbd "<f7>"))
(global-set-key (kbd "<f7>") 'my-grep-marked)
