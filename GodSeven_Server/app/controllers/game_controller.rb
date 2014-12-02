require 'uuidtools'
class GameController < ApplicationController
  	def setup
	  	uuid = params[:uuid]
		if uuid
			if uuid.eql?("")
				uuid = UUIDTools::UUID.timestamp_create.to_s.gsub('-','')
			end
			if @user = User.find_or_create_by!(uuid: uuid)
				logger.error "Game Setup 32311: #{params}"
				@user.update_attributes(ipaddress: ip_address)
			end
			render :json  => {message: "Game Setup OK"}.to_json, :status => 200
		else
			logger.error "Game Setup Error: #{params}"
      		render :json  => {}, :status => 400
		end
  	end
end
