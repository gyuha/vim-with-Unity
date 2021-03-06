" vim:foldmethod=marker:fen:
scriptencoding utf-8

" Load Once {{{
if exists('g:loaded_openbrowser') && g:loaded_openbrowser
    finish
endif
let g:loaded_openbrowser = 1
" }}}
" Saving 'cpoptions' {{{
let s:save_cpo = &cpo
set cpo&vim
" }}}


let s:is_unix = has('unix')
let s:is_mswin = has('win16') || has('win32') || has('win64')
let s:is_cygwin = has('win32unix')
let s:is_macunix = has('macunix')
lockvar s:is_unix
lockvar s:is_mswin
lockvar s:is_cygwin
lockvar s:is_macunix

if !(s:is_unix || s:is_mswin || s:is_cygwin || s:is_macunix)
    echohl WarningMsg
    echomsg 'Your platform is not supported!'
    echohl None
    finish
endif

" Save booleans for autoload/openbrowser.vim
let g:__openbrowser_platform = {
\   'unix': s:is_unix,
\   'mswin': s:is_mswin,
\   'cygwin': s:is_cygwin,
\   'macunix': s:is_macunix,
\}

" Interfaces {{{

" For backward compatibility,
" - OpenBrowser()
" - OpenBrowserSearch()

" Open URL with `g:openbrowser_open_commands`.
function! OpenBrowser(...) "{{{
    return call('openbrowser#open', a:000)
endfunction "}}}

function! OpenBrowserSearch(...) "{{{
    return call('openbrowser#search', a:000)
endfunction "}}}



" Ex command
command!
\   -bar -nargs=+ -complete=file
\   OpenBrowser
\   call openbrowser#open(<q-args>)
command!
\   -bar -nargs=+ -complete=customlist,openbrowser#_cmd_complete_open_browser_search
\   OpenBrowserSearch
\   call openbrowser#_cmd_open_browser_search(<q-args>)



" Key-mapping
nnoremap <Plug>(openbrowser-open) :<C-u>call openbrowser#_keymapping_open('n')<CR>
vnoremap <Plug>(openbrowser-open) :<C-u>call openbrowser#_keymapping_open('v')<CR>

" }}}


" Restore 'cpoptions' {{{
let &cpo = s:save_cpo
" }}}
