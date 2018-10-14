const fs = require('fs');
var style_customer = "";
var style_code = "";

var front_measurements_list = [];
var front_tolerance_list = [];
var front_xxs_list = [];
var front_xs_list = [];
var front_s_list = [];
var front_m_list = [];
var front_l_list = [];
var front_xl_list = [];

var back_measurements_list = [];
var back_tolerance_list = [];
var back_xxs_list = [];
var back_xs_list = [];
var back_s_list = [];
var back_m_list = [];
var back_l_list = [];
var back_xl_list = [];


function add_front(){
  
    $('#front-measure').append( '<tr>\
  <td><input type="text" name="measurement" class="measurement" style="width:100%"/></td>\
  <td><input type="text" name="tolerance" class="tolerance"/></td>\
  <td><input type="text" name="xxs" class="xxs"/></td>\
  <td><input type="text" name="xs" class="xs"/></td>\
  <td><input type="text" name="s" class="s"/></td>\
  <td><input type="text" name="m" class="m"/></td>\
  <td><input type="text" name="l" class="l"/></td>\
  <td><input type="text" name="xl" class="xl"/></td>\
  </tr>' );
  }

  function add_back(){
  
    $('#back-measure').append( '<tr>\
    <td><input type="text" name="measurement" class="measurement" style="width:100%"/></td>\
    <td><input type="text" name="tolerance" class="tolerance"/></td>\
    <td><input type="text" name="xxs" class="xxs"/></td>\
    <td><input type="text" name="xs" class="xs"/></td>\
    <td><input type="text" name="s" class="s"/></td>\
    <td><input type="text" name="m" class="m"/></td>\
    <td><input type="text" name="l" class="l"/></td>\
    <td><input type="text" name="xl" class="xl"/></td>\
    </tr>' );
  }

  function store_style(){
  
    $('#front-measure tr td .measurement').each(function() {
      // console.log("printing elements" + $(this)[0]);
      var label = $(this).val();  
      //console.log("Html:" + $(this).html());  
      console.log("Name:" + label); 
      front_measurements_list.push(label);
   });
   $('#front-measure tr td .tolerance').each(function() {
    // console.log("printing elements" + $(this)[0]);
    var label = $(this).val();  
    //console.log("Html:" + $(this).html());  
    console.log("Name:" + label); 
    front_tolerance_list.push(label);
 });
 $('#front-measure tr td .xxs').each(function() {
    // console.log("printing elements" + $(this)[0]);
    var label = $(this).val();  
    //console.log("Html:" + $(this).html());  
    console.log("Name:" + label); 
    front_xxs_list.push(label);
 });
 $('#front-measure tr td .xs').each(function() {
    // console.log("printing elements" + $(this)[0]);
    var label = $(this).val();  
    //console.log("Html:" + $(this).html());  
    console.log("Name:" + label); 
    front_xs_list.push(label);
 });
 $('#front-measure tr td .s').each(function() {
    // console.log("printing elements" + $(this)[0]);
    var label = $(this).val();  
    //console.log("Html:" + $(this).html());  
    console.log("Name:" + label); 
    front_s_list.push(label);
 });
 $('#front-measure tr td .m').each(function() {
    // console.log("printing elements" + $(this)[0]);
    var label = $(this).val();  
    //console.log("Html:" + $(this).html());  
    console.log("Name:" + label); 
    front_m_list.push(label);
 });
 $('#front-measure tr td .l').each(function() {
    // console.log("printing elements" + $(this)[0]);
    var label = $(this).val();  
    //console.log("Html:" + $(this).html());  
    console.log("Name:" + label); 
    front_l_list.push(label);
 });
 $('#front-measure tr td .xl').each(function() {
    // console.log("printing elements" + $(this)[0]);
    var label = $(this).val();  
    //console.log("Html:" + $(this).html());  
    console.log("Name:" + label); 
    front_xl_list.push(label);
 });




 $('#back-measure tr td .measurement').each(function() {
    // console.log("printing elements" + $(this)[0]);
    var label = $(this).val();  
    //console.log("Html:" + $(this).html());  
    console.log("Name:" + label); 
    back_measurements_list.push(label);
 });
 $('#back-measure tr td .tolerance').each(function() {
  // console.log("printing elements" + $(this)[0]);
  var label = $(this).val();  
  //console.log("Html:" + $(this).html());  
  console.log("Name:" + label); 
  back_tolerance_list.push(label);
});
$('#back-measure tr td .xxs').each(function() {
  // console.log("printing elements" + $(this)[0]);
  var label = $(this).val();  
  //console.log("Html:" + $(this).html());  
  console.log("Name:" + label); 
  back_xxs_list.push(label);
});
$('#back-measure tr td .xs').each(function() {
  // console.log("printing elements" + $(this)[0]);
  var label = $(this).val();  
  //console.log("Html:" + $(this).html());  
  console.log("Name:" + label); 
  back_xs_list.push(label);
});
$('#back-measure tr td .s').each(function() {
  // console.log("printing elements" + $(this)[0]);
  var label = $(this).val();  
  //console.log("Html:" + $(this).html());  
  console.log("Name:" + label); 
  back_s_list.push(label);
});
$('#back-measure tr td .m').each(function() {
  // console.log("printing elements" + $(this)[0]);
  var label = $(this).val();  
  //console.log("Html:" + $(this).html());  
  console.log("Name:" + label); 
  back_m_list.push(label);
});
$('#back-measure tr td .l').each(function() {
  // console.log("printing elements" + $(this)[0]);
  var label = $(this).val();  
  //console.log("Html:" + $(this).html());  
  console.log("Name:" + label); 
  back_l_list.push(label);
});
$('#back-measure tr td .xl').each(function() {
  // console.log("printing elements" + $(this)[0]);
  var label = $(this).val();  
  //console.log("Html:" + $(this).html());  
  console.log("Name:" + label); 
  back_xl_list.push(label);
});
  
  build_config();
  }

  function build_config(){
    // style_name = $('#text-style').val();
    style_customer = $('#text-customer').val();
    style_code = $('#text-code').val();
    $('#btn_train').css('visibility','visible');
    
    try { 
      filename = style_code + '_style' ;
      var front_panel_data = [];
      var back_panel_data = [];
      //building array of values
      for(i = 0;i < front_measurements_list.length; i++){
        front_panel_data.push({"measurement_name":front_measurements_list[i],"tolerance":front_tolerance_list[i],"xxs":front_xxs_list[i],
        "xs":front_xs_list[i],"s":front_s_list[i],"m":front_m_list[i],"l":front_l_list[i],"xl":front_xl_list[i]});
        
  
  
      }
      for(i = 0;i < back_measurements_list.length; i++){
        back_panel_data.push({"measurement_name":back_measurements_list[i],"tolerance":back_tolerance_list[i],"xxs":back_xxs_list[i],
        "xs":back_xs_list[i],"s":back_s_list[i],"m":back_m_list[i],"l":back_l_list[i],"xl":back_xl_list[i]});
        
  
  
      }
      // config = { "imagePath":filename+'.jpg',"style":style_name, "points":points, "code":style_code ,"size":style_size ,"measurements":measurement_data};
  
  
      config = { "style_code":style_code, "customer":style_customer, "front_panel":front_panel_data ,"back_panel":back_panel_data};
      let data = JSON.stringify(config);  
      fs.writeFileSync('core/styles/'+ filename +'.json', data, 'utf-8', 4); 
     
      
      
    }catch(e) { 
      console.log('Failed to save the file ! ' + e); 
    }
    
    console.log("[+]Writing complete!");
  }
  function send_to_server(){

  }