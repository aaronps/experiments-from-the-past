/** 
 * @constructor For loading and read ftp files.
 */
function RemoteFile()
{
    /**@type String */
    this.list_remote_files_url = "rs/remotentcip/";
    
    /**@type String */
    this.get_remote_file_url = "rs/remotentcip/";

    /**@type String */
    this.put_remote_file_url = "rs/remotentcip/";

    /**@type String */
    this.post_remote_file_url = "rs/remotentcip/";

    /**@type String */
    this.rest_load_function_tag = 'get';
    
    /**@type String */
    this.rest_generate_function_tag = 'save';

}

/**
 * Load the configuration file.
 * @param {Object} viewer        The configuration viewer object
 * @param {string} rel_url       Relative url
 * @param {string} data_type     Received data type
 * @param {string} success_func  success function
 * @param {string} error_func  error function
 */
RemoteFile.prototype.do_loading = function( viewer, rel_url, data_type, success_func, error_func )
{
    var url = this.get_remote_file_url 
            + this.rest_load_function_tag
            + rel_url;
        
    jQuery.ajax(
    {
        context:viewer,
        type:"GET",
        url:url,
        parseData: false,
        data:"",
        dataType:data_type,
        success:success_func,
        error:error_func
    });
};

/**
 * Uploading function to upload the configuration file.
 * @param {Object} viewer        The configuration viewer object
 * @param {string} rel_url       Relative url
 * @param {string} data          Received data type
 * @param {string} success_func  success function
 * @param {string} error_func    error function
 */
RemoteFile.prototype.do_uploading = function( viewer, rel_url, data, success_func, error_func )
{
    var url = this.get_remote_file_url 
            + this.rest_generate_function_tag 
            + rel_url;

    jQuery.ajax(
    {
        context:viewer,
        type:"PUT",
        contentType:"application/octet-stream",
        url:url,
        parseData: false,
        processData: false,
        data:data,
        dataType:"text",
        success:success_func,
        error:error_func
    });    
};

/**
 * Load the file indicated by the url parameter, 
 * touch off the corresponding function.
 * @param {Object} context Ajax context
 * @param {String} rel_url relative getting url
 * @param {String} receiver_func Correspending function name
 */
RemoteFile.prototype.select_file = function( context, rel_url, receiver_func )
{
    Util.startFancybox();
    
    var url = this.get_remote_file_url + rel_url;
    var _receiver_func = receiver_func;
    
    jQuery.ajax(
    {
        context:context,
        type:"GET",
        url:url,
        parseData: false,
        data:"",
        dataType:"text",
        success:function(text){
            if ( _receiver_func != null )
            {
                this[_receiver_func](text);
            }
            Util.stopFancybox();
        },
        error:function(xhr, text, excep) {
            Util.stopFancybox();
            Util.alertInfo('error receiving files');
        }
    });
}

/**
 * Load the file list indicated by the url parameter, 
 * touch off the corresponding function.
 * @param {Object} context Ajax context
 * @param {String} rel_url Relative getting url
 * @param {String} receiver_func Correspending function name
 */
RemoteFile.prototype.reload_list = function( context, rel_url, receiver_func)
{
    Util.startFancybox();
    
    var url = this.list_remote_files_url + rel_url;
    
    var _receiver_func = receiver_func;
    jQuery.ajax(
    {
        context: context,
        type:"GET",
        url:url,
        parseData: true,
        data:"",
        dataType:"xml",
        success:function(xml){
            this[_receiver_func](xml);
            Util.stopFancybox();
        },
        error:function(){
            Util.alertInfo('error receiving files');
            Util.stopFancybox();
        }
    });
};

/**
 * Put the given data to the given url.
 * @param {Object} context Ajax context
 * @param {String} rel_url relative url
 * @param {String} data
 */
RemoteFile.prototype.put_file = function ( context, rel_url, data )
{
    Util.startFancybox();
    
    var url = this.put_remote_file_url + rel_url;
    
    jQuery.ajax(
    {
        context:context,
        type:"PUT",
        contentType:"application/octet-stream",
        url:url,
        parseData: false,
        processData: false,
        data:data,
        dataType:"text",
        success:function(){
            Util.alertInfo('file put ok');

            Util.stopFancybox();
        },
        error:function(xhr, text, excep) {
            Util.alertInfo('error putting file');
    
            Util.stopFancybox();
        }
    });
};

/**
 * Post the given text to the given url.
 * @param {Object} context Ajax context
 * @param {String} rel_url relative url
 * @param {String} text
 */
RemoteFile.prototype.post_file = function( context, rel_url, text)
{
    var sep = 'TELVENTPOST' + +new Date();
    
    var url = this.post_remote_file_url + rel_url;

    var data_to_send = [ '--',sep, '\r\n',
        'Content-Disposition: form-data; name="filedata"; filename="datafile.adb"', '\r\n',
        'Content-Type: application/octet-stream', '\r\n',
        '\r\n',
        text, '\r\n'
    ]
    
    Util.startFancybox();
    
    jQuery.ajax(
    {
        context:context,
        type:"POST",
        encoding: '',
        contentType:"multipart/form-data;boundary=" + sep,
        url: url,
        parseData: false,
        processData: false,
        data: data_to_send.join(''),
        dataType:"text",
        success:function()
        {
//            Util.alertInfo('file posted ok');
            Util.stopFancybox();
        },
        error:function(xhr, text, excep)
        {
            Util.alertInfo('error posting file');
            Util.stopFancybox();
        }
    });
}

/**
 * @param {HTMLFormElement} form
 * @param {string} rel_url
 */
RemoteFile.prototype.upload_file = function( form, rel_url )
{
    form.action = this.post_remote_file_url + rel_url;
    
    form.submit();
}

/**
 * @param {string} rel_url
 */
RemoteFile.prototype.save_as_local = function( rel_url )
{
    var url = this.get_remote_file_url + rel_url;
    
    window.open( url );
}