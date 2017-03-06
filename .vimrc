" Import Local vimrc
set exrc
set secure

" Bundles
execute pathogen#infect()
filetype plugin indent on
" Autosave
let g:auto_save = 1
let g:auto_save_in_insert_mode = 0  " do not save while in insert mode

"Indentation
set autoindent
set expandtab
set softtabstop=4
set shiftwidth=4
set tw=80

" Useful information
set showcmd
set relativenumber
set number

" Undo directory
set undofile
set undodir="~/.vim/undofiles"

"pretty color
set background=dark
syntax on
hi Normal ctermbg=black ctermfg=grey
hi CursorLine ctermbg=yellow ctermfg=black 
set cursorline

