/*
Copyright (c) 2003-2011, CKSource - Frederico Knabben. All rights reserved.
For licensing, see LICENSE.html or http://ckeditor.com/license
*/

/*
 * This file is used/requested by the 'Styles' button.
 * The 'Styles' button is not enabled by default in DrupalFull and DrupalFiltered toolbars.
 */
if(typeof(CKEDITOR) !== 'undefined') {
  
    CKEDITOR.addStylesSet( 'drupal',
    [
       //Backgrounds
       { name : 'Background Accent'     , element : {div:1, p:1, span:1, ul:1, ol:1, dl:1, dd:1, h1:1, h2:1, h3:1, h4:1, h5:1, h6:1, table:1, img:1}, attributes : { 'class' : 'background-accent' } },
       { name : 'Background Dark'       , element : {div:1, p:1, span:1, ul:1, ol:1, dl:1, dd:1, h1:1, h2:1, h3:1, h4:1, h5:1, h6:1, table:1, img:1}, attributes : { 'class' : 'background-dark' } },
       { name : 'Background Highlight'	, element : {div:1, p:1, span:1, ul:1, ol:1, dl:1, dd:1, h1:1, h2:1, h3:1, h4:1, h5:1, h6:1, table:1, img:1}, attributes : { 'class' : 'background-highlight' } },
       { name : 'Background Light'      , element : {div:1, p:1, span:1, ul:1, ol:1, dl:1, dd:1, h1:1, h2:1, h3:1, h4:1, h5:1, h6:1, table:1, img:1}, attributes : { 'class' : 'background-light' } },
       { name : 'Background White'      , element : {div:1, p:1, span:1, ul:1, ol:1, dl:1, dd:1, h1:1, h2:1, h3:1, h4:1, h5:1, h6:1, table:1, img:1}, attributes : { 'class' : 'background-white' } },
       { name : 'Width 10'              , element : {div:1, p:1, span:1, ul:1, ol:1, dl:1, dd:1, h1:1, h2:1, h3:1, h4:1, h5:1, h6:1, table:1, img:1}, attributes : { 'class' : 'width-10' } },
       { name : 'Width 20'              , element : {div:1, p:1, span:1, ul:1, ol:1, dl:1, dd:1, h1:1, h2:1, h3:1, h4:1, h5:1, h6:1, table:1, img:1}, attributes : { 'class' : 'width-20' } },
       { name : 'Width 30'              , element : {div:1, p:1, span:1, ul:1, ol:1, dl:1, dd:1, h1:1, h2:1, h3:1, h4:1, h5:1, h6:1, table:1, img:1}, attributes : { 'class' : 'width-30' } },
       { name : 'Width 40'              , element : {div:1, p:1, span:1, ul:1, ol:1, dl:1, dd:1, h1:1, h2:1, h3:1, h4:1, h5:1, h6:1, table:1, img:1}, attributes : { 'class' : 'width-40' } },
       { name : 'Width 50'              , element : {div:1, p:1, span:1, ul:1, ol:1, dl:1, dd:1, h1:1, h2:1, h3:1, h4:1, h5:1, h6:1, table:1, img:1}, attributes : { 'class' : 'width-50' } },
       { name : 'Width 60'              , element : {div:1, p:1, span:1, ul:1, ol:1, dl:1, dd:1, h1:1, h2:1, h3:1, h4:1, h5:1, h6:1, table:1, img:1}, attributes : { 'class' : 'width-60' } },    
       { name : 'Width 70'              , element : {div:1, p:1, span:1, ul:1, ol:1, dl:1, dd:1, h1:1, h2:1, h3:1, h4:1, h5:1, h6:1, table:1, img:1}, attributes : { 'class' : 'width-70' } },    
       { name : 'Width 80'              , element : {div:1, p:1, span:1, ul:1, ol:1, dl:1, dd:1, h1:1, h2:1, h3:1, h4:1, h5:1, h6:1, table:1, img:1}, attributes : { 'class' : 'width-80' } },    
       { name : 'Width 90'              , element : {div:1, p:1, span:1, ul:1, ol:1, dl:1, dd:1, h1:1, h2:1, h3:1, h4:1, h5:1, h6:1, table:1, img:1}, attributes : { 'class' : 'width-90' } },    
       { name : 'Width 100'             , element : {div:1, p:1, span:1, ul:1, ol:1, dl:1, dd:1, h1:1, h2:1, h3:1, h4:1, h5:1, h6:1, table:1, img:1}, attributes : { 'class' : 'width-100' } },           
          
    ]);
}