var img = document.getElementById('train_image');
var canvas= document.getElementById("point-canvas");
var ctx = document.getElementById('point-canvas').getContext("2d");
var xpos;
var ypos;
var style_name = "";
var style_country = "";
var stage;
var points = ([]);
var i = 0;
var point_no = 0;
const fs = require('fs');
const point_name = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','u','p'];
function init(){
    $('#train_image').css('height', $('#train_image').naturalHeight);
    $('#train_image').css('width', $('#train_image').naturalWidth); 
    
    
}

function show_inputs(){//after clicking new
    
    $('.input-container').css('visibility','visible');
    $('#btn_new').css('visibility','hidden');
    $('#btn_cancel').css('visibility','visible');
    $('#btn_submit').css('visibility','visible');
    
    
    
}
function activate_canvas(){//after submit
  $("#train_image").attr("src","http://localhost:5000/video_feed");
  $('#point-canvas').css('cursor', 'crosshair');
  point_no = 0;

  
  

  stage = new createjs.Stage("point-canvas");
 
  stage.on("stagemousedown",function(event){
    console.log("clicked:" + event.stageX + "," + event.stageY);
    // point = new createjs.Shape();
    

    var g = new createjs.Graphics();
    g.setStrokeStyle(1);
    g.beginStroke(createjs.Graphics.getRGB(0,0,0));
    g.beginFill(createjs.Graphics.getRGB(255,0,0));
    g.drawCircle(0,0,3);
    point = new createjs.Shape(g);

    var text = new createjs.Text(point_name[point_no], "20px Arial", "#ff7700");
    
    text.x = event.stageX;
    text.y = event.stageY;
    text.textBaseline = "alphabetic";
   
    
    // point.graphics.beginFill("blue").drawCircle(0, 0, 2);
    point.x = event.stageX;
    point.y = event.stageY;
    
    console.log("[+]Image width:" + img.width);
    console.log("[+]Image Natural:" + img.naturalWidth);
    points.push([event.stageX / img.width * img.naturalWidth, event.stageY / img.height * img.naturalHeight]);
    console.log(points[0])
    stage.addChild(point);
    stage.addChild(text);
    stage.update();
    add_table(point_name[point_no], event.stageX, event.stageY);
    point_no++;


  })
}
function cancel(){
    $('.input-container').css('visibility','hidden');
    $('#btn_new').css('visibility','visible');
    $('#btn_cancel').css('visibility','hidden');
    $('#btn_submit').css('visibility','hidden');
}
function submit_fun(){
  activate_canvas();
  style_name = $('#text-style').val();
  style_country = $('#text-country').val();
  console.log("style: " + style_name + "  country:" + style_country);
  $('.input-container').css('visibility','hidden');
  $('#btn_submit').css('visibility','hidden');
  $('#btn_next').css('visibility','visible');
  // $("#train_image").attr("src","second.jpg");
  
    
}
$('.input-container input').blur(function(event) {
    var inputVal = this.value;
    
    if (inputVal) {
      this.classList.add('value-exists');
    } else {
      this.classList.remove('value-exists');
    }
  });
function build_config(){
  
  $('#btn_train').css('visibility','visible');
  
  try { 
    filename = style_name + '_' + i ;
    config = { "imagePath":filename+'.jpg',"style":style_name, "points":points, "country":style_country };
    let data = JSON.stringify(config);  
    fs.writeFileSync('core/data/'+ filename +'.json', data, 'utf-8', 4); 
    $.post( "http://localhost:5000/capture", { file: filename } );
    points = ([]);
    
  }catch(e) { 
    console.log('Failed to save the file !'); 
  }
  i++;
  stage.removeAllChildren();
  stage.update();

  console.log("[+]Writing complete!");
} 

function next(){
  build_config();

}
function start_train(){
  $.get('http://localhost:5000/train',function(data){
      
    console.log("Training Response:" + data)
    
      
  });
}
function add_measurement(){
  $('#measurement-table').append( '<tr><td><input type="text" name="measurement"/></td><td><input type="text" name="sp"/></td><td><input type="text" name="ep"/></td></tr>' );
}
function add_table(label, xcor, ycor){
  $('#point-locations').append( '<tr>\
  <th>'+label+'</th>\
  <td>'+ xcor +'</td>\
  <td>'+ ycor +'</td>\
  </tr>');
}




  init();