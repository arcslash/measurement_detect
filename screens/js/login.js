
// (function ($) {
//     "use strict";


//     /*==================================================================
//     [ Validate ]*/
//     var input = $('.validate-input .input100');

//     $('.validate-form').on('submit',function(){
//         var check = true;

//         // for(var i=0; i<input.length; i++) {
//         //     if(validate(input[i]) == false){
//         //         showValidate(input[i]);
//         //         check=false;
//         //     }
//         // }
//         //
//         // return check
//         var username = $('#field_user');
//         var password = $('#field_pass');
//         console.log("Username:"+username + "  Password:" + password);
        
//     });


//     $('.validate-form .input100').each(function(){
//         $(this).focus(function(){
//            showValidate(this);
//         });
//     });

//     function validate (input) {
//         if($(input).attr('type') == 'email' || $(input).attr('name') == 'email') {
//             if($(input).val().trim().match(/^([a-zA-Z0-9_\-\.]+)@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.)|(([a-zA-Z0-9\-]+\.)+))([a-zA-Z]{1,5}|[0-9]{1,3})(\]?)$/) == null) {
//                 return false;
//             }
//         }
//         else {
//             if($(input).val().trim() == ''){
//                 return false;
//             }
//         }
//     }

//     function showValidate(input) {
//         var thisAlert = $(input).parent();

//         $(thisAlert).addClass('alert-validate');
//     }

//     function hideValidate(input) {
//         var thisAlert = $(input).parent();

//         $(thisAlert).removeClass('alert-validate');
//     }





// })(jQuery);

function login_validate(){
    // window.location.replace("dashboard.html");
    location.href='dashboard.html'
    // var user = $("#email").val();
    // var password = $("#pass").val();
    // console.log("Email:" + user  + "  Pass:"+ password);
    // if(password == "12345"){
    //     console.log("Password Correct!")
    //     window.location.replace("dashboard.html");
    // }else{
    //     window.location.replace("google.com");
    // }
}
