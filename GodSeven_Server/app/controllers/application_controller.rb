require 'ipaddr'
class ApplicationController < ActionController::Base
  # Prevent CSRF attacks by raising an exception.
  # For APIs, you may want to use :null_session instead.
  # protect_from_forgery with: :exception

  def api_version
    @api_version ||= Gem::Version.new(params[:api_version])
  end

  def error_404(msg = "Can not found resource")
    render :json => {message: msg}.to_json, :status => 404
  end

  def error_500(msg)
    render :json => {message: msg}.to_json, :status => 500
  end

  def error_500_for_ar(object)
    error_500 object.errors.full_messages.join('\n')
  end

  def ip_address
    if request.headers["HTTP_X_FORWARDED_FOR"].nil?
      return 0
    else
      ip = request.headers["HTTP_X_FORWARDED_FOR"].split(",").first || "0.0.0.0"
      IPAddr.new( ip.strip ).native.to_i
    end
  rescue
    0
  end
end
