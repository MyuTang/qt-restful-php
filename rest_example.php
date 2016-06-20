<?php
	if(isset($_POST['id'])){
		$headers = getallheaders();
		if(isset($headers['appKey'])){
			$key = $headers['appKey'];
			if($key == 'tejashwi'){
				$id = $_POST['id'];
				$hash = md5($id);
				$data = array('id' => $id, 'md5' => $hash, 'message' => 'success');
				exit(json_encode($data));
			}else
				exit(json_encode(array('message' => 'Invalid application key')));
		}
		else
			exit(json_encode(array('message' => 'No application key provided')));
	}else
		exit(json_encode(array('message' => 'No input ID provided')));
?>